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

#include "include/renderer/RenderBackend.hpp"

#include <eigen2/Eigen/LU>

#include "include/renderer/MaterialBase.hpp"
#include "include/renderer/GeometryBase.hpp"
#include "include/utils/debug.hpp"
#include "include/traverser/LightNode.hpp"
#include "include/traverser/GeometryNode.hpp"
#include "include/traverser/CameraNode.hpp"

#include "include/renderer/FrameBufferObject.hpp"

namespace gua {

    Texture* tmptex(NULL);
    Texture* tmpdepth(NULL);
    FrameBufferObject* tmpfbo(NULL);

RenderBackend::RenderBackend( int width, int height, std::string const& camera, std::string const& display ):
    window_(width, height, display),
    camera_name_(camera) {}

void RenderBackend::render( std::vector<GeometryNode*> const& node_list,
                            std::vector<LightNode*> const& light_list,
                            CameraNode* camera ) {

    if (!tmptex) {
        tmptex = new Texture(800, 600);
        tmpdepth = new Texture(800, 600, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT);
        tmpdepth->set_parameter(GL_TEXTURE_COMPARE_MODE, GL_NONE);
        tmpdepth->set_parameter(GL_DEPTH_TEXTURE_MODE, GL_ALPHA);

        tmpfbo = new FrameBufferObject();

        tmpfbo->attach_buffer(window_.get_context(), GL_TEXTURE_2D, tmptex->get_id(window_.get_context()), GL_COLOR_ATTACHMENT0);
        tmpfbo->attach_buffer(window_.get_context(), GL_TEXTURE_2D, tmpdepth->get_id(window_.get_context()), GL_DEPTH_ATTACHMENT);
    }

    window_.set_active();
    window_.start_frame();

    if (camera) {
        Eigen::Matrix4f view_matrix(camera->transform_.inverse());

        // --- bind g buffer
        // --- use fill shader

        tmpfbo->bind(window_.get_context(), {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT});

        // clear the G-Buffer
        glClearColor(0.0, 1.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        for (auto& geometry_core: node_list) {

            auto material = MaterialBase::instance()->get(geometry_core->material_);
            auto geometry = GeometryBase::instance()->get(geometry_core->geometry_);

            if (material) {
                material->use(window_.get_context());
                if (material->get_texture())
                    material->get_texture()->bind(window_.get_context(), 0);
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

        tmpfbo->unbind();






        for (auto& geometry_core: node_list) {

            auto material = MaterialBase::instance()->get(geometry_core->material_);
            auto geometry = GeometryBase::instance()->get(geometry_core->geometry_);

            if (material) {
                material->use(window_.get_context());

                tmptex->bind(window_.get_context(), 0);

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

        // --- unuse fill shader
        // --- unbind g buffer

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
