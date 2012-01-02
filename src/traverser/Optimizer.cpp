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
#include "include/traverser/Optimizer.hpp"

#include "include/traverser/LightNode.hpp"
#include "include/traverser/GeometryNode.hpp"
#include "include/traverser/CameraNode.hpp"
#include "include/scenegraph/Core.hpp"
#include "include/scenegraph/CameraCore.hpp"
#include "include/scenegraph/GeometryCore.hpp"
#include "include/scenegraph/LightCore.hpp"
#include "include/scenegraph/Node.hpp"
#include "include/scenegraph/SceneGraph.hpp"
#include "include/scenegraph/Iterator.hpp"

#include <stack>
#include <eigen2/Eigen/Geometry>

namespace gua {

Optimizer::Optimizer() {
}

Optimizer::~Optimizer() {
	for ( auto geometry( geometry_data_.begin()); geometry != geometry_data_.end(); ++geometry ) {
		delete (*geometry);
	}

	for ( auto light( light_data_.begin()); light != light_data_.end(); ++light ) {
		delete (*light);
	}

	for ( auto camera( camera_data_.begin()); camera != camera_data_.end(); ++ camera ) {
		delete (*camera);
	}
}



void Optimizer::check( SceneGraph const* scene_graph ) {
	// clearing all old data
	int geometry_count = geometry_data_.size();
	for ( auto geometry( geometry_data_.begin()); geometry != geometry_data_.end(); ++geometry ) {
		delete (*geometry);
	}
	geometry_data_.clear();
	geometry_data_.reserve( geometry_count );
	// assuming the number of nodes stays quite constant through time, reserving the old size might save some time
	int light_count = light_data_.size();
	for ( auto light( light_data_.begin() ); light != light_data_.end(); ++ light ) {
		delete (*light);
	}
	light_data_.clear();
	light_data_.reserve( light_count );

	int camera_count = camera_data_.size();
	for ( auto camera( camera_data_.begin() ); camera != camera_data_.end(); ++ camera ) {
		delete (*camera);
	}
	camera_data_.clear();
	camera_data_.reserve( camera_count );



	auto node = scene_graph->begin();

	Eigen::Matrix4f identity_matrix = Eigen::Matrix4f::Identity();


	std::stack< Eigen::Matrix4f > matrix_stack;

	matrix_stack.push(identity_matrix);

	int depth = 0;
	do {

		Core* current_core( node.get_core() );
		Eigen::Matrix4f  current_matrix( matrix_stack.top() * node.get_transform() );

		if (current_core) {
            switch ( current_core->get_type() ) {
            case Core::CoreType::CAMERA : {
                auto camera_core = reinterpret_cast<CameraCore*>  ( current_core );
                CameraNode* render_camera = new CameraNode( camera_core->get_frustum(), current_matrix );
                camera_data_.push_back( render_camera );
                // TODO do better camera handling and use std::map to handel it
                break;
            }
            case Core::CoreType::LIGHT : {
                //auto light_core =  reinterpret_cast<LightCore*>  ( current_core );
                // TODO add lightColor to LightNode
                LightNode* render_light = new LightNode( current_matrix );
                light_data_.push_back( render_light );
                break;
            }
            case Core::CoreType::GEOMETRY : {
                auto geometry_core = reinterpret_cast<GeometryCore*> ( current_core );
                GeometryNode* render_geometry = new GeometryNode( geometry_core->get_geometry(), geometry_core->get_material(), current_matrix );
                geometry_data_.push_back( render_geometry );
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
			for (; depth > new_depth; --depth) {
				matrix_stack.pop();
			}
		};
		} while ( node != scene_graph->end() );

}


std::vector<GeometryNode*> const& Optimizer::get_geometry_data() const {
	return geometry_data_;
}


std::vector<LightNode*> const& Optimizer::get_light_data() const {
	return light_data_;
}

std::vector<CameraNode*> const& Optimizer::get_camera_data() const {
	return camera_data_;
}

}