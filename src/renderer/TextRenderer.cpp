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
/// \brief Definition of the TextRenderer class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/TextRenderer.hpp"

#include "utils/string_utils.hpp"

namespace gua {

TextRenderer::TextRenderer(RenderContext const& context) {
    scm::gl::font_face_ptr counter_font(new scm::gl::font_face(context.render_device, "/usr/share/fonts/truetype/freefont/FreeSans.ttf", 24, 0.7f, scm::gl::font_face::smooth_normal));
    text_renderer_.reset(new scm::gl::text_renderer(context.render_device));
    frame_counter_text_.reset(new scm::gl::text(context.render_device, counter_font, scm::gl::font_face::style_regular, "Application FPS: 0"));
    frame_counter_text_->text_color(scm::math::vec4f(1.0f, 1.0f, 0.0f, 1.0f));
    frame_counter_text_->text_outline_color(scm::math::vec4f(0.0f, 0.0f, 0.0f, 1.0f));
    frame_counter_text_->text_kerning(true);
}

void TextRenderer::render_fps(RenderContext const& context,
                              FrameBufferObject& target,
                              float application_fps, float rendering_fps) const {

    target.bind(context);

    scm::math::mat4f fs_projection = scm::math::make_ortho_matrix(0.0f, static_cast<float>(target.width()),
                                                                  0.0f, static_cast<float>(target.height()), -1.0f, 1.0f);
    text_renderer_->projection_matrix(fs_projection);

    frame_counter_text_->text_string("Application FPS: " + string_utils::to_string(application_fps) + "\n" + "Rendering FPS: " + string_utils::to_string(rendering_fps));

    scm::math::vec2i text_ur = scm::math::vec2i(40, target.height() - frame_counter_text_->text_bounding_box().y + 10);
    text_renderer_->draw_outlined(context.render_context, text_ur, frame_counter_text_);

    target.unbind(context);
}

}
