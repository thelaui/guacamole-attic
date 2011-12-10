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
/// \brief Declaration of the internal renderer.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/RenderBackend.hpp"

#include <eigen2/Eigen/LU>

#include "include/renderer/MaterialBase.hpp"
#include "include/renderer/GeometryBase.hpp"
#include "include/utils/debug.hpp"
#include "include/renderer/tmp/tmp.hpp"

RenderBackend::RenderBackend( int width, int height, std::string const& display ):
    window_(width, height, display) {}

void RenderBackend::render( std::vector<GeometryCore*> const& node_list,
                            std::vector<LightCore*> const& light_list,
                            CameraCore const& camera ) {

    window_.set_active();
    window_.start_frame();

    Eigen::Matrix4f view_matrix(camera.transform_.matrix().inverse());

    for (auto& geometry_core: node_list) {

        auto material = MaterialBase::pointer()->get(geometry_core->material_);
        auto geometry = GeometryBase::pointer()->get(geometry_core->geometry_);

        if (material) {
            material->use(window_.get_context());
            material->get_shader().set_projection_matrix(window_.get_context(), camera.projection_);
            material->get_shader().set_view_matrix(window_.get_context(), view_matrix);
            material->get_shader().set_model_matrix(window_.get_context(), geometry_core->transform_.matrix());
        } else {
            WARNING("Cannot use material \"%s\": Undefined material name!", geometry_core->material_.c_str());
        }

        if (geometry) {
            window_.draw(geometry);
        } else {
            WARNING("Cannot draw geometry \"%s\": Undefined geometry name!", geometry_core->geometry_.c_str());
        }
    }

    window_.finish_frame();
}


