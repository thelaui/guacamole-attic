////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
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
/// \brief Definition of the TextRenderer class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/TextRenderer.hpp"

// guacamole headers
#include "utils/string_utils.hpp"
#include "utils/math.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

TextRenderer::
TextRenderer(RenderContext const& ctx) {

    scm::gl::font_face_ptr font(new scm::gl::font_face(
                            ctx.render_device,
                            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
                            24, 0.7f, scm::gl::font_face::smooth_normal));

    text_renderer_.reset(new scm::gl::text_renderer(ctx.render_device));

    frame_counter_text_.reset(new scm::gl::text(
                            ctx.render_device, font,
                            scm::gl::font_face::style_regular,
                            "Application FPS: 0"));

    frame_counter_text_->text_color(math::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    frame_counter_text_->text_outline_color(math::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    frame_counter_text_->text_kerning(true);
}

////////////////////////////////////////////////////////////////////////////////

void TextRenderer::
render_fps(RenderContext const& ctx, FrameBufferObject& target,
           float application_fps, float rendering_fps) const {

    target.bind(ctx);

    math::mat4 fs_projection = scm::math::make_ortho_matrix(
                                  0.0f, static_cast<float>(target.width()),
                                  0.0f, static_cast<float>(target.height()),
                                  -1.0f, 1.0f);

    text_renderer_->projection_matrix(fs_projection);

    frame_counter_text_->text_string("Application FPS: "
                            + string_utils::to_string(application_fps)
                            + "\nRendering FPS: "
                            + string_utils::to_string(rendering_fps));

    math::vec2i text_ur = math::vec2i(40, target.height()
                            - frame_counter_text_->text_bounding_box().y + 10);

    text_renderer_->draw_outlined(
                            ctx.render_context, text_ur, frame_counter_text_);

    target.unbind(ctx);
}

////////////////////////////////////////////////////////////////////////////////

}
