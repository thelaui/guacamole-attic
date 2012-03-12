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
#include <eigen2/Eigen/SVD>

#include "renderer/MaterialBase.hpp"
#include "renderer/GeometryBase.hpp"
#include "renderer/LightSphere.hpp"
#include "renderer/BufferFillShaders.hpp"
#include "traverser/OptimizedScene.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"
#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"


namespace gua {

void RenderBackend::render(std::string const& camera_name, std::string const& screen_name,
                           OptimizedScene const& scene, FrameBufferObject& fbo,
                           RenderContext const& context) {

    fbo.bind(context, {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT});

    glClearColor(0.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto camera_it(scene.cameras_.find(camera_name));
    auto screen_it(scene.screens_.find(screen_name));

    if (camera_it != scene.cameras_.end() && screen_it != scene.screens_.end()) {
        auto camera(camera_it->second);
        auto screen(screen_it->second);
        auto projection(math::compute_frustum(Eigen::Transform3f(camera.transform_).translation(), screen.transform_, 0.1, 1000.f));

        Eigen::Transform3f camera_transform(screen.transform_);
        camera_transform.data()[12] = 0.f;
        camera_transform.data()[13] = 0.f;
        camera_transform.data()[14] = 0.f;
        camera_transform.data()[15] = 1.f;

        camera_transform = camera_transform.pretranslate(Eigen::Transform3f(camera.transform_).translation());

        Eigen::Matrix4f view_matrix(camera_transform.matrix().inverse());

        for (auto& geometry_core: scene.nodes_) {

            auto geometry = GeometryBase::instance()->get(geometry_core.geometry_);
            auto material = MaterialBase::instance()->get(geometry_core.material_);

            if (material && geometry) {
                material->use(context);

                material->get_shader().set_mat4(context, "projection_matrix", projection);
                material->get_shader().set_mat4(context, "view_matrix", view_matrix);
                material->get_shader().set_mat4(context, "model_matrix", geometry_core.transform_);
                material->get_shader().set_mat4(context, "normal_matrix", geometry_core.transform_.inverse().transpose());

                geometry->draw(context);

                material->unuse(context);

            } else if (material) {
                WARNING("Cannot render geometry \"%s\": Undefined geometry name!", geometry_core.geometry_.c_str());
            } else if (geometry) {
                WARNING("Cannot render geometry \"%s\": Undefined material name: \"%s\"!", geometry_core.geometry_.c_str(), geometry_core.material_.c_str());
            } else {
                WARNING("Cannot render geometry \"%s\": Undefined geometry and material name: \"%s\"!", geometry_core.geometry_.c_str(), geometry_core.material_.c_str());
            }
        }
    }

    fbo.unbind();
}

}
