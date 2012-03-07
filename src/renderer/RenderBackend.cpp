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
/// \brief Definition of the RenderBackend class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/RenderBackend.hpp"

#include "renderer/MaterialBase.hpp"
#include "renderer/GeometryBase.hpp"
#include "renderer/BufferFillShaders.hpp"
#include "traverser/OptimizedScene.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"
#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"


namespace gua {

RenderBackend::RenderBackend( int width, int height, std::string const& camera, std::string const& screen, std::string const& display ):
    window_(width, height, "Displaying "+ camera + " at display" + display + ".", display),
    camera_name_(camera),
    screen_name_(screen),
    light_sphere_(new Geometry("data/objects/light_sphere.obj")),
    depth_buffer_(width, height, scm::gl::FORMAT_D24_S8),
    color_buffer_(width, height),
    position_buffer_(width, height),
    normal_buffer_(width, height),
    g_buffer_(),
    buffer_fill_shader_(),
    deferred_light_shader_(),
    blend_state_(),
    rasterizer_state_(),
    depth_stencil_state_() {
        buffer_fill_shader_.create_from_sources(BUFFER_FILL_VERTEX_SHADER, BUFFER_FILL_FRAGMENT_SHADER);
        deferred_light_shader_.create_from_files("data/shaders/deferred_light.vert", "data/shaders/deferred_light.frag");
//
//        depth_buffer_.set_parameter(GL_TEXTURE_COMPARE_MODE, GL_NONE);
//        depth_buffer_.set_parameter(GL_DEPTH_TEXTURE_MODE, GL_ALPHA);
//
        g_buffer_.attach_color_buffer(window_.get_context(), 0, color_buffer_);
        g_buffer_.attach_color_buffer(window_.get_context(), 1, position_buffer_);
        g_buffer_.attach_color_buffer(window_.get_context(), 2, normal_buffer_);
        g_buffer_.attach_depth_stencil_buffer(window_.get_context(), depth_buffer_);

        blend_state_ = window_.get_context().render_device->create_blend_state(true, scm::gl::FUNC_ONE, scm::gl::FUNC_ONE,
                                                                                     scm::gl::FUNC_ONE, scm::gl::FUNC_ONE);
        rasterizer_state_ = window_.get_context().render_device->create_rasterizer_state(scm::gl::FILL_SOLID, scm::gl::CULL_FRONT);
        depth_stencil_state_ = window_.get_context().render_device->create_depth_stencil_state(false, false, scm::gl::COMPARISON_NEVER);
}

void RenderBackend::render(OptimizedScene const& scene) {

    window_.set_active(true);
    window_.start_frame();

    auto camera_it(scene.cameras_.find(camera_name_));
    auto screen_it(scene.screens_.find(screen_name_));

    if (camera_it != scene.cameras_.end() && screen_it != scene.screens_.end()) {
        auto camera(camera_it->second);
        auto screen(screen_it->second);

        if (camera.type_ == CameraCore::MONO) {
            math::mat4 camera_transform(camera.transform_);
            auto projection(math::compute_frustum(camera_transform.column(3), screen.transform_, 0.1, 1000.f));
            render_eye(scene.nodes_, scene.lights_, projection, camera_transform.column(3), math::mat4(screen.transform_), camera.type_, true);
        } else {
            math::mat4 eye_position(camera.transform_);

            scm::math::translate(eye_position, -camera.stereo_width_*0.5f, 0.f, 0.f);
            auto projection(math::compute_frustum(eye_position.column(3), screen.transform_, 0.1, 1000.f));
            render_eye(scene.nodes_, scene.lights_, projection, eye_position.column(3), math::mat4(screen.transform_), camera.type_, true);

            window_.get_context().render_context->clear_default_depth_stencil_buffer();

            scm::math::translate(eye_position, camera.stereo_width_, 0.f, 0.f);
            projection = math::compute_frustum(eye_position.column(3), screen.transform_, 0.1, 1000.f);
            render_eye(scene.nodes_, scene.lights_, projection, eye_position.column(3), math::mat4(screen.transform_), camera.type_, false);
        }

    }

    window_.finish_frame();
}

void RenderBackend::render_eye(std::vector<GeometryNode> const& node_list,
                   std::vector<LightNode> const& light_list,
                   math::mat4 const& camera_projection,
                   math::vec3 const& camera_position,
                   math::mat4 const& screen_transform,
                   CameraCore::Type camera_type,
                   bool is_left_eye) {

    math::mat4 camera_transform(screen_transform);
    camera_transform[12] = 0.f;
    camera_transform[13] = 0.f;
    camera_transform[14] = 0.f;
    camera_transform[15] = 1.f;

    camera_transform = scm::math::make_translation(camera_position) * camera_transform;

    math::mat4 view_matrix(scm::math::inverse(camera_transform));

    enable_stereo(camera_type, is_left_eye);

    fill_g_buffer(node_list, camera_projection, view_matrix);

    window_.get_context().render_context->set_blend_state(blend_state_);
    window_.get_context().render_context->set_rasterizer_state(rasterizer_state_);
    window_.get_context().render_context->set_depth_stencil_state(depth_stencil_state_);

    float texel_width((camera_type == CameraCore::SIDE_BY_SIDE ? 2.f : 1.f) / window_.get_context().width);
    float x_fragment_offset(!is_left_eye && camera_type == CameraCore::SIDE_BY_SIDE ?  1.f : 0.f);

    deferred_light_shader_.use(window_.get_context());

    deferred_light_shader_.set_mat4(window_.get_context(), "projection_matrix", camera_projection);
    deferred_light_shader_.set_mat4(window_.get_context(), "view_matrix", view_matrix);
    deferred_light_shader_.set_sampler2D(window_.get_context(), "color_buffer", color_buffer_);
    deferred_light_shader_.set_sampler2D(window_.get_context(), "position_buffer", position_buffer_);
    deferred_light_shader_.set_sampler2D(window_.get_context(), "normal_buffer", normal_buffer_);
    deferred_light_shader_.set_float(window_.get_context(), "texel_width", texel_width);
    deferred_light_shader_.set_float(window_.get_context(), "texel_height", 1.f/window_.get_context().height);
    deferred_light_shader_.set_float(window_.get_context(), "x_fragment_offset", x_fragment_offset);

    for (auto& light: light_list) {
        deferred_light_shader_.set_mat4(window_.get_context(), "model_matrix", light.transform_);
        deferred_light_shader_.set_mat4(window_.get_context(), "normal_matrix", scm::math::transpose(scm::math::inverse(light.transform_)));
        deferred_light_shader_.set_color3f(window_.get_context(), "light_color", light.color_);

        window_.draw(light_sphere_);
    }

    deferred_light_shader_.unuse(window_.get_context());

    window_.get_context().render_context->reset_state_objects();

    disable_stereo();
}

void RenderBackend::fill_g_buffer(std::vector<GeometryNode> const& node_list,
                   math::mat4 const& camera_projection,
                   math::mat4 const& view_matrix) {

    g_buffer_.bind(window_.get_context());

    g_buffer_.clear_color_buffers(window_.get_context());
    g_buffer_.clear_depth_stencil_buffer(window_.get_context());

    buffer_fill_shader_.use(window_.get_context());

    buffer_fill_shader_.set_mat4(window_.get_context(), "projection_matrix", camera_projection);
    buffer_fill_shader_.set_mat4(window_.get_context(), "view_matrix", view_matrix);

    for (auto& geometry_core: node_list) {

        auto geometry = GeometryBase::instance()->get(geometry_core.geometry_);

        buffer_fill_shader_.set_mat4(window_.get_context(), "model_matrix", geometry_core.transform_);
        buffer_fill_shader_.set_mat4(window_.get_context(), "normal_matrix",  scm::math::transpose(scm::math::inverse(geometry_core.transform_)));

        if (geometry) {
            window_.draw(geometry);
        } else {
            WARNING("Cannot render geometry to g-buffer\"%s\": Undefined geometry name!", geometry_core.geometry_.c_str());
        }
    }

    buffer_fill_shader_.unuse(window_.get_context());

    g_buffer_.unbind(window_.get_context());
}

void RenderBackend::enable_stereo(CameraCore::Type camera_type, bool is_left_eye) {
    switch(camera_type) {
        case CameraCore::ANAGLYPH_RED_CYAN: {
            glColorMask(is_left_eye, !is_left_eye, !is_left_eye, !is_left_eye);
        } break;

        case CameraCore::ANAGLYPH_RED_GREEN: {
            glColorMask(is_left_eye, !is_left_eye, false, !is_left_eye);
        } break;

        case CameraCore::SIDE_BY_SIDE: {
            if (is_left_eye)
                glViewport(0, 0, window_.get_context().width*0.5, window_.get_context().height);
            else
                glViewport(window_.get_context().width*0.5, 0, window_.get_context().width*0.5, window_.get_context().height);
        } break;

        default:;
    }
}

void RenderBackend::disable_stereo() {
    glViewport(0.f, 0.f, window_.get_context().width, window_.get_context().height);
    glColorMask(true, true, true, true);
}

}
