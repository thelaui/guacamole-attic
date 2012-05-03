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
/// \brief Definition of the Optimizer class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "traverser/Optimizer.hpp"

// guacamole headers
#include "scenegraph/Core.hpp"
#include "cores/CameraCore.hpp"
#include "cores/GeometryCore.hpp"
#include "cores/LightCore.hpp"
#include "scenegraph/Node.hpp"
#include "scenegraph/SceneGraph.hpp"
#include "scenegraph/Iterator.hpp"

// external headers
#include <stack>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

Optimizer::
Optimizer():
    data_() {}

////////////////////////////////////////////////////////////////////////////////

Optimizer::
~Optimizer() {}

////////////////////////////////////////////////////////////////////////////////

void Optimizer::
check(SceneGraph const* scene_graph, RenderMask const& render_mask) {

    // clearing all old data
    int geometry_count = data_.nodes_.size();
    data_.nodes_.clear();
    data_.nodes_.reserve(geometry_count);

    // assuming the number of nodes stays quite constant through time,
    // reserving the old size might save some time
    int light_count = data_.lights_.size();
    data_.lights_.clear();
    data_.lights_.reserve(light_count);

    data_.screens_.clear();
    data_.cameras_.clear();

    auto node = scene_graph->get_iterator("/");

    std::stack<math::mat4> matrix_stack;
    matrix_stack.push(math::mat4::identity());

    std::stack<std::set<std::string>> groups_stack;

    int depth = 0;
    while (node != scene_graph->end()) {
        Core* current_core(node.get_core());
        math::mat4 curr_mat(matrix_stack.top() * node.get_transform());

        std::set<std::string> curr_grp;

        if (!groups_stack.empty())
            curr_grp.insert(
                        groups_stack.top().begin(), groups_stack.top().end());

        curr_grp.insert(
                        node.get_groups().begin(), node.get_groups().end());

        if (current_core) {
            switch (current_core->get_type()) {

                case Core::CoreType::CAMERA : {
                    // cameras are always added
                    auto core = reinterpret_cast<CameraCore*>(current_core);

                    data_.cameras_.insert(
                                std::make_pair(node.get_name(),
                                               CameraNode(*core, curr_mat)));
                    break;

                } case Core::CoreType::LIGHT : {
                    // lights are only added when their groups fit
                    if (render_mask.check(curr_grp)) {
                        auto core = reinterpret_cast<LightCore*>(
                                                                 current_core);
                        data_.lights_.push_back(
                                    LightNode(curr_mat, core->get_color()));
                    } break;

                } case Core::CoreType::SCREEN : {
                    // screens are always added
                    auto core = reinterpret_cast<ScreenCore*>(current_core);

                    math::mat4 scale(scm::math::make_scale(
                                core->get_width(), core->get_height(), 1.f));

                    data_.screens_.insert(
                                std::make_pair(node.get_name(), ScreenNode(
                                                            curr_mat * scale)));
                    break;

                } case Core::CoreType::GEOMETRY : {
                    // geometry is only added when its groups fit
                    if (render_mask.check(curr_grp)) {
                        auto core = reinterpret_cast<GeometryCore*>(
                                                                current_core);
                        data_.nodes_.push_back(
                                GeometryNode(core->get_geometry(),
                                             core->get_material(), curr_mat));
                    }
                } default:;
            }
        }

        ++node;

        int new_depth = node.get_depth();
        if (new_depth > depth) {
            matrix_stack.push(curr_mat);
            groups_stack.push(curr_grp);
            depth = new_depth;
        } else {
            while (depth > new_depth) {
                matrix_stack.pop();
                groups_stack.pop();
                --depth;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

OptimizedScene const& Optimizer::
get_data() const {

    return data_;
}

////////////////////////////////////////////////////////////////////////////////

}
