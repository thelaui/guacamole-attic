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
/// \brief Definition of the Optimizer class.
////////////////////////////////////////////////////////////////////////////////
#include "traverser/Optimizer.hpp"

#include "scenegraph/Core.hpp"
#include "cores/CameraCore.hpp"
#include "cores/GeometryCore.hpp"
#include "cores/LightCore.hpp"
#include "scenegraph/Node.hpp"
#include "scenegraph/SceneGraph.hpp"
#include "scenegraph/Iterator.hpp"

#include <stack>
#include <eigen2/Eigen/Geometry>

namespace gua {

Optimizer::Optimizer() {
}

Optimizer::~Optimizer() {
}

void Optimizer::check( SceneGraph const* scene_graph ) {

    // clearing all old data
    int geometry_count = data_.nodes_.size();
    data_.nodes_.clear();
    data_.nodes_.reserve( geometry_count );

    // assuming the number of nodes stays quite constant through time, reserving the old size might save some time
    int light_count = data_.lights_.size();
    data_.lights_.clear();
    data_.lights_.reserve( light_count );

    data_.screens_.clear();
    data_.cameras_.clear();

    auto node = scene_graph->begin();

    std::stack<Eigen::Matrix4f> matrix_stack;
    matrix_stack.push(Eigen::Matrix4f::Identity());

    int depth = 0;
    do {

        Core* current_core( node.get_core() );
        Eigen::Matrix4f current_matrix( matrix_stack.top() * node.get_transform() );

        if (current_core) {
            switch ( current_core->get_type() ) {
            case Core::CoreType::CAMERA : {
                auto camera_core = reinterpret_cast<CameraCore*>  ( current_core );
                data_.cameras_.insert( std::make_pair( node.get_name(), CameraNode( *camera_core, current_matrix ) ));
                break;
            }
            case Core::CoreType::LIGHT : {
                auto light_core = reinterpret_cast<LightCore*>  ( current_core );
                data_.lights_.push_back( LightNode( current_matrix, light_core->get_color()) );
                break;
            }
            case Core::CoreType::SCREEN : {
                auto screen_core = reinterpret_cast<ScreenCore*>  ( current_core );
                Eigen::Transform3f scale((Eigen::Transform3f)Eigen::Matrix4f::Identity());
                scale.scale(Eigen::Vector3f(screen_core->get_width(), screen_core->get_height(), 1));
                data_.screens_.insert( std::make_pair(node.get_name(), ScreenNode(current_matrix * scale)) );
                break;
            }
            case Core::CoreType::GEOMETRY : {
                auto geometry_core = reinterpret_cast<GeometryCore*> ( current_core );
                data_.nodes_.push_back( GeometryNode( geometry_core->get_geometry(), geometry_core->get_material(), current_matrix ) );
                break;
            }
            default: break;
            }
        }

        ++node;
        int new_depth = node.get_depth();
        if (new_depth > depth){
            matrix_stack.push( current_matrix );
            depth = new_depth;
        } else {
            for (; depth > new_depth; --depth)
                matrix_stack.pop();
        }
    } while ( node != scene_graph->end() );

}


OptimizedScene const& Optimizer::get_data() const {
    return data_;
}

}
