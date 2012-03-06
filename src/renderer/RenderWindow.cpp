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

namespace gua {

unsigned RenderWindow::last_context_id_ = 0;

RenderWindow::RenderWindow( int width, int height, std::string const& window_title, std::string const& display_string ) {

    scm::gl::wm::surface::format_desc window_format(scm::gl::FORMAT_RGBA_8,
                                              scm::gl::FORMAT_D24_S8,
                                              true /*double_buffer*/,
                                              false /*quad_buffer*/);
    scm::gl::wm::context::attribute_desc context_attribs(3, //SCM_GL_CORE_OPENGL_VERSION / 100,
                                                3, //SCM_GL_CORE_OPENGL_VERSION / 10 % 10,
                                                false /*compatibility*/,
                                                false /*debug*/,
                                                false /*forward*/);

    ctx_.display = scm::gl::wm::display_ptr(new scm::gl::wm::display(display_string));
    ctx_.window = scm::gl::wm::window_ptr (new scm::gl::wm::window(ctx_.display, 0, window_title,
                                          scm::math::vec2i(0, 0), scm::math::vec2ui(width, height),
                                          window_format));
    ctx_.context = scm::gl::wm::context_ptr(new scm::gl::wm::context(ctx_.window, context_attribs));

    ctx_.window->show();

    set_active(true);

    ctx_.render_device = scm::gl::render_device_ptr(new scm::gl::render_device());
    ctx_.render_context = ctx_.render_device->main_context();

    ctx_.width = width;
    ctx_.height = height;
    ctx_.id = last_context_id_++;

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

void RenderWindow::draw(std::shared_ptr<Geometry> const& geometry) const {
    geometry->draw(ctx_);
}

void RenderWindow::init(int argc, char** argv) {
    static scm::shared_ptr<scm::core> scm_core(new scm::core(argc, argv));
}

RenderContext const& RenderWindow::get_context() const {
    return ctx_;
}

}

