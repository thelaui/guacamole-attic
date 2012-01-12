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

namespace gua {

RenderBackend::RenderBackend( int width, int height, std::string const& camera, std::string const& display ):
    window_(width, height, display),
    camera_name_(camera) {}

void RenderBackend::render( std::vector<GeometryNode*> const& node_list,
                            std::vector<LightNode*> const& light_list,
                            CameraNode* camera ) {

    window_.set_active();
    window_.start_frame();

    if (camera) {
        Eigen::Matrix4f view_matrix(camera->transform_.inverse());

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
    }

    window_.finish_frame();
}

std::string const& RenderBackend::get_camera_name() const {
    return camera_name_;
}

}
