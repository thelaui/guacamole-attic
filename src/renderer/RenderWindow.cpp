////////////////////////////////////////////////////////////////////////////////
// guacamole - an interesting scenegraph implementation
//
// Copyright (c) 2011 by Mischa Krempel, Felix Lauer and Simon Schneegans
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Definition of the RenderWindow class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/RenderWindow.hpp"

#include "utils/debug.hpp"
#include "renderer/Geometry.hpp"
#include "renderer/Texture.hpp"
#include "renderer/StereoShaders.hpp"

#include <sstream>
#include <iostream>

namespace gua {

unsigned RenderWindow::last_context_id_ = 0;

RenderWindow::RenderWindow( Description const& description ) throw (std::string):
    fullscreen_shader_(),
    frames_(0),
    frame_count_(0),
    frames_start_(0),
    fullscreen_quad_(),
    depth_stencil_state_() {

    fullscreen_shader_.create_from_sources(STEREO_VERTEX_SHADER.c_str(), STEREO_FRAGMENT_SHADER.c_str());

    scm::gl::wm::surface::format_desc window_format(scm::gl::FORMAT_RGBA_8,
                                              scm::gl::FORMAT_D24_S8,
                                              true /*double_buffer*/,
                                              false /*quad_buffer*/);
    scm::gl::wm::context::attribute_desc context_attribs(3, //SCM_GL_CORE_OPENGL_VERSION / 100,
                                                3, //SCM_GL_CORE_OPENGL_VERSION / 10 % 10,
                                                false /*compatibility*/,
                                                false /*debug*/,
                                                false /*forward*/);

    ctx_.display = scm::gl::wm::display_ptr(new scm::gl::wm::display(description.display));
    ctx_.window = scm::gl::wm::window_ptr (new scm::gl::wm::window(ctx_.display, 0, description.title,
                                          scm::math::vec2i(0, 0), scm::math::vec2ui(description.width, description.height),
                                          window_format));
    ctx_.context = scm::gl::wm::context_ptr(new scm::gl::wm::context(ctx_.window, context_attribs));

    ctx_.window->show();

    set_active(true);

    ctx_.render_device = scm::gl::render_device_ptr(new scm::gl::render_device());
    ctx_.render_context = ctx_.render_device->main_context();

    ctx_.width = description.width;
    ctx_.height = description.height;
    ctx_.id = last_context_id_++;

    fullscreen_quad_ = scm::gl::quad_geometry_ptr(new scm::gl::quad_geometry(ctx_.render_device,
                                                                             math::vec2(-1.f, -1.f),
                                                                             math::vec2( 1.f,  1.f)));

    depth_stencil_state_ = ctx_.render_device->create_depth_stencil_state(false, false, scm::gl::COMPARISON_NEVER);

    start_frame();
    finish_frame();
    //set_active(false);

}

RenderWindow::~RenderWindow() {

}

void RenderWindow::set_active(bool active) const {
    ctx_.context->make_current(ctx_.window, active);
}

void RenderWindow::start_frame() const {
    ctx_.render_context->clear_default_color_buffer(scm::gl::FRAMEBUFFER_BACK, scm::math::vec4f(0.f, 0.f, 0.f, 1.0f));
    ctx_.render_context->clear_default_depth_stencil_buffer();
}

void RenderWindow::finish_frame() const {
    set_active(true);
    ctx_.window->swap_buffers(0);
}

void RenderWindow::display_mono(std::shared_ptr<Texture> const& texture) {
    display_stereo(texture, texture, MONO);
}

void RenderWindow::display_stereo(std::shared_ptr<Texture> const& left_texture,
                                  std::shared_ptr<Texture> const& right_texture,
                                  StereoMode stereo_mode) {

    ctx_.render_context->set_viewport(scm::gl::viewport(scm::math::vec2ui(0,0), scm::math::vec2ui(ctx_.width, ctx_.height)));

    fullscreen_shader_.use(ctx_);

    fullscreen_shader_.set_sampler2D(ctx_, "left_tex", *left_texture);
    fullscreen_shader_.set_sampler2D(ctx_, "right_tex", *right_texture);
    fullscreen_shader_.set_int(ctx_, "mode", stereo_mode);

    ctx_.render_context->set_depth_stencil_state(depth_stencil_state_);

    fullscreen_quad_->draw(ctx_.render_context);

    ctx_.render_context->reset_state_objects();
    fullscreen_shader_.unuse(ctx_);
}

RenderContext const& RenderWindow::get_context() const {
    return ctx_;
}

}

