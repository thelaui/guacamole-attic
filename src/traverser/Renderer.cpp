#include "include/traverser/Renderer.hpp"

#include "include/scenegraph/SceneGraph.hpp"
#include "include/renderer/RenderBackend.hpp"
#include "include/traverser/Optimizer.hpp"

Renderer::Renderer():
    optimizer_( new Optimizer() )
    {
    }

Renderer::~Renderer(){
    delete optimizer_;
    for ( auto backend( render_backend_list_.begin() ); backend != render_backend_list_.end(); ++backend ){
            delete (*backend);
    }
}

void Renderer::open_display( int width, int height, std::string const& display ) {
    RenderBackend* the_new_backend( new RenderBackend( width , height, display ) );
    render_backend_list_.push_back( the_new_backend );
}

void Renderer::start_render_loop( SceneGraph const* scene_graph ) {
	while (true) {
		optimizer_->check( scene_graph );
		for ( auto backend( render_backend_list_.begin() ); backend != render_backend_list_.end(); ++ backend ) {
			(*backend)->render( optimizer_->get_geometry_data(), optimizer_->get_light_data(), optimizer_->get_camera_data()[0] );	
		}
	}
}

