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
#include "utils/debug.hpp"
#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"

namespace gua {

RenderBackend::RenderBackend( int width, int height, std::string const& camera, std::string const& display ):
    window_(width, height, display),
    camera_name_(camera),
    light_sphere_(LIGHT_SPHERE_DATA.c_str(), LIGHT_SPHERE_DATA.length()),
    depth_buffer_(width, height, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT),
    color_buffer_(width, height),
    position_buffer_(width, height),
    normal_buffer_(width, height),
    g_buffer_(),
    buffer_fill_shader_(VertexShader(BUFFER_FILL_VERTEX_SHADER.c_str()),
                        FragmentShader(BUFFER_FILL_FRAGMENT_SHADER.c_str())),
    deferred_light_shader_() {

        depth_buffer_.set_parameter(GL_TEXTURE_COMPARE_MODE, GL_NONE);
        depth_buffer_.set_parameter(GL_DEPTH_TEXTURE_MODE, GL_ALPHA);

        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, position_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, normal_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0 +1);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, color_buffer_.get_id(window_.get_context()), GL_COLOR_ATTACHMENT0 +2);
        g_buffer_.attach_buffer(window_.get_context(), GL_TEXTURE_2D, depth_buffer_.get_id(window_.get_context()), GL_DEPTH_ATTACHMENT);
    }

void RenderBackend::render( std::vector<GeometryNode*> const& node_list,
                            std::vector<LightNode*> const& light_list,
                            CameraNode* camera ) {
    window_.set_active();
    window_.start_frame();

    if (camera) {
        Eigen::Matrix4f view_matrix(camera->transform_.inverse());

        // --- bind g buffer
        // --- use fill shader


        g_buffer_.bind(window_.get_context(), {GL_COLOR_ATTACHMENT0,
                                               GL_COLOR_ATTACHMENT0 +1,
                                               GL_COLOR_ATTACHMENT0 +2});

        // clear the G-Buffer
        glViewport(0, 0, window_.get_context().width, window_.get_context().height);
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        buffer_fill_shader_.use(window_.get_context());

        for (auto& geometry_core: node_list) {

            auto material = MaterialBase::instance()->get(geometry_core->material_);
            auto geometry = GeometryBase::instance()->get(geometry_core->geometry_);

            if (material) {
                material->use(window_.get_context());

                material->get_shader().set_projection_matrix(window_.get_context(), camera->projection_);
                material->get_shader().set_view_matrix(window_.get_context(), view_matrix);
                material->get_shader().set_model_matrix(window_.get_context(), geometry_core->transform_);
            } else {
                WARNING("Cannot use material \"%s\": Undefined material name!", geometry_core->material_.c_str());
            }

            if (geometry) {
                window_.draw(geometry);
            } else {
                WARNING("Cannot draw geometry \"%s\": Undefined geometry name!", geometry_core->geometry_.c_str());
            }
        }

        buffer_fill_shader_.unuse();

        g_buffer_.unbind();


        for (auto& geometry_core: node_list) {

            auto material = MaterialBase::instance()->get(geometry_core->material_);
            auto geometry = GeometryBase::instance()->get(geometry_core->geometry_);

            if (material) {
                material->use(window_.get_context());

                material->get_shader().set_projection_matrix(window_.get_context(), camera->projection_);
                material->get_shader().set_view_matrix(window_.get_context(), view_matrix);
                material->get_shader().set_model_matrix(window_.get_context(), geometry_core->transform_);
            } else {
                WARNING("Cannot use material \"%s\": Undefined material name!", geometry_core->material_.c_str());
            }

            if (geometry) {
                window_.draw(geometry);
            } else {
                WARNING("Cannot draw geometry \"%s\": Undefined geometry name!", geometry_core->geometry_.c_str());
            }
        }



        // --- bind light sphere
        // --- bind deferred shader
        // --- use g buffer as sampler3D

        // --- render lights

        // --- unbind stuff
    }

    window_.finish_frame();
}

std::string const& RenderBackend::get_camera_name() const {
    return camera_name_;
}

}
