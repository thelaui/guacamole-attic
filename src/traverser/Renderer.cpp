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
/// \brief Definition of the Render class.
////////////////////////////////////////////////////////////////////////////////
#include "include/traverser/Renderer.hpp"

#include "include/scenegraph/SceneGraph.hpp"
#include "include/renderer/RenderBackend.hpp"
#include "include/traverser/Optimizer.hpp"

Renderer::Renderer(int width, int height, std::string const& display):
    optimizer_( new Optimizer() ) {

    RenderBackend* the_new_backend( new RenderBackend( width , height, display ) );
    render_backend_list_.push_back( the_new_backend );
}

Renderer::~Renderer(){
    delete optimizer_;
    for ( auto backend( render_backend_list_.begin() ); backend != render_backend_list_.end(); ++backend ){
            delete (*backend);
    }
}

void Renderer::start_render_loop( SceneGraph const* scene_graph ) {
	while (true) {
		optimizer_->check( scene_graph );
		for ( auto backend( render_backend_list_.begin() ); backend != render_backend_list_.end(); ++ backend ) {
			(*backend)->render( optimizer_->get_geometry_data(), optimizer_->get_light_data(), optimizer_->get_camera_data()[0] );
		}
	}
}

