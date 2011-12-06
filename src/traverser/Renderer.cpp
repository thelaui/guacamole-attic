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
    for ( auto backend : renderer_backend_list_ ){
            delete backend;
    }
}

void Renderer::open_display( int width, int height, std::string display ) {
    RenderBackend* the_new_backend( new RenderBackend( width , height, display ) );
    render_backend_list.push_back( the_new_backend );
}

void Renderer::start_render_loop( SceneGraph const* scene_graph ) {
	while (true) {
		optimizer_->check( scene_graph );
		for ( auto backend : renderer_backend_list_ ) {
			backend->render( optimizer_->geometry_data, optimizer_->light_data, *(optimizer->camera_data[0]) );	
		}
	}
}

