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

#include <eigen2/Eigen/LU>

#include "renderer/MaterialBase.hpp"
#include "renderer/GeometryBase.hpp"
#include "renderer/LightSphere.hpp"
#include "renderer/BufferFillShaders.hpp"
#include "traverser/OptimizedScene.hpp"
#include "utils/debug.hpp"
#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"


namespace gua {

RenderBackend::RenderBackend( int width, int height, std::string const& camera, std::string const& display ):
    window_(width, height, display),
    camera_name_(camera),
    light_sphere_(new Geometry(LIGHT_SPHERE_DATA.c_str(), LIGHT_SPHERE_DATA.length())),
    depth_buffer_(width, height, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT),
    color_buffer_(width, height),
    position_buffer_(width, height),
    normal_buffer_(width, height),
    g_buffer_(),
    buffer_fill_shader_(VertexShader(BUFFER_FILL_VERTEX_SHADER.c_str()),
                        FragmentShader(BUFFER_FILL_FRAGMENT_SHADER.c_str())),
    deferred_light_shader_(VertexShader(std::string("data/shaders/deferred_light.vert")),
                           FragmentShader(std::string("data/shaders/deferred_light.frag"))) {

        depth_buffer_.set_parameter(GL_TEXTURE_COMPARE_MODE, GL_NONE);
        depth_buffer_.set_parameter(GL_DEPTH_TEXTURE_MODE, GL_ALPHA);

        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, color_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, position_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0 +1);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, normal_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0 +2);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, depth_buffer_.get_id(window_.get_context()), GL_DEPTH_ATTACHMENT);

}

void RenderBackend::render(OptimizedScene const& scene) {

    window_.set_active();
    window_.start_frame();

    auto camera_it(scene.cameras_.find(camera_name_));

    if (camera_it != scene.cameras_.end()) {
        auto camera(camera_it->second);

        if (camera.type_ == CameraCore::MONO) {
            render_eye(scene.nodes_, scene.lights_, camera.projection_, camera.transform_, camera.type_, true);
        } else {
            Eigen::Transform3f eye_position(camera.transform_);

            eye_position.translate(Eigen::Vector3f(-camera.stereo_width_*0.5, 0, 0));
            render_eye(scene.nodes_, scene.lights_, camera.projection_, eye_position.matrix(), camera.type_, true);

            glClear(GL_DEPTH_BUFFER_BIT);

            eye_position.translate(Eigen::Vector3f(camera.stereo_width_, 0, 0));
            render_eye(scene.nodes_, scene.lights_, camera.projection_, eye_position.matrix(), camera.type_, false);
        }

    }

    window_.finish_frame();
}

void RenderBackend::render_eye(std::vector<GeometryNode> const& node_list,
                   std::vector<LightNode> const& light_list,
                   Eigen::Matrix4f const& camera_projection,
                   Eigen::Matrix4f const& camera_transform,
                   CameraCore::Type camera_type,
                   bool is_left_eye) {

    Eigen::Matrix4f view_matrix(camera_transform.inverse());

    fill_g_buffer(node_list, camera_projection, view_matrix);

    enable_stereo(camera_type, is_left_eye);

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

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
        deferred_light_shader_.set_mat4(window_.get_context(), "normal_matrix", light.transform_.inverse().transpose());
        deferred_light_shader_.set_vec3(window_.get_context(), "light_color", light.color_);

        window_.draw(light_sphere_);
    }

    deferred_light_shader_.unuse();

    glPopAttrib();

    disable_stereo();
}

void RenderBackend::fill_g_buffer(std::vector<GeometryNode> const& node_list,
                   Eigen::Matrix4f const& camera_projection,
                   Eigen::Matrix4f const& view_matrix) {

    g_buffer_.bind(window_.get_context(), {GL_COLOR_ATTACHMENT0,
                                           GL_COLOR_ATTACHMENT0 +1,
                                           GL_COLOR_ATTACHMENT0 +2});

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    buffer_fill_shader_.use(window_.get_context());

    buffer_fill_shader_.set_mat4(window_.get_context(), "projection_matrix", camera_projection);
    buffer_fill_shader_.set_mat4(window_.get_context(), "view_matrix", view_matrix);

    for (auto& geometry_core: node_list) {

        auto geometry = GeometryBase::instance()->get(geometry_core.geometry_);

        buffer_fill_shader_.set_mat4(window_.get_context(), "model_matrix", geometry_core.transform_);
        buffer_fill_shader_.set_mat4(window_.get_context(), "normal_matrix", geometry_core.transform_.inverse().transpose());

        if (geometry) {
            window_.draw(geometry);
        } else {
            WARNING("Cannot render geometry to g-buffer\"%s\": Undefined geometry name!", geometry_core.geometry_.c_str());
        }
    }

    buffer_fill_shader_.unuse();

    g_buffer_.unbind();
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
