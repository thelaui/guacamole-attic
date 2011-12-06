#include "include/traverser/Optimizer.hpp"


#include "include/scenegraph/Core.hpp"
#include "include/scenegraph/Camera.hpp"
#include "include/scenegraph/Geometry.hpp"
#include "include/scenegraph/Light.hpp"
#include "include/scenegraph/Node.hpp"
#include "include/scenegraph/SceneGraph.hpp"


Optimizer::Optimizer() {
}

Optimizer::~Optimizer() {

	for ( auto geometry : geometry_data_ ) {
		delete geometry;
	}

	for ( auto light : light_data_ ) {
		delete light;
	}

	for ( auto camera : camera_data_ ) {
		delete camera;
	}


}



void Optimizer::check( SceneGraph const* scene_graph ) {
	// clearing all old data
	int geometry_count = geometry_data_.size();
	for ( auto geometry: geometry_data_ ) {
		delete geometry;
	}
	geometry_data_.clear();
	geometry_data_.reserve( geometry_count ); 
	// assuming the number of nodes stays quite constant through time, reserving the old size might save some time
	int light_count = light_data_.size();
	for ( auto light: light_data_ ) {
		delete light;
	}
	light_data_.clear();
	light_data_.reserve( light_count );

	int camera_count = camera_data_.size();
	for ( auto camera: camera_data_ ) {
		delete camera;
	}
	camera_data_.clear();
	camera_data_.reserve( camera_count );


	Node* root = scene_graph->get_root();
	
	Eigen::Matrix4f identity_matrix = Eigen::Matrix4f::Identity();
	
	traverse_( root, identity_matrix );
	

}



void Optimizer::traverse_( Node* current_node, Eigen::Matrix4f const& current_matrix ) {
	std::shared_ptr<Core> current_core( current_node->get_core() );
	Eigen::Matrix4f new_current_matrix( current_matrix * current_core->get_transform() );
	switch ( current_core.get_type() ) {
		case Core::CoreType::CAMERA : {
		 	std::shared_ptr<Camera> camera_core = static_cast< std::shared_ptr<Camera> > ( current_core );
			Camera* render_camera = new Camera( );
			// TODO set other Values
			camera_data_.push_back( render_camera );
			// TODO do better camera handling and use std::map to handel it
			break;
		} 
		case Core::CoreType::LIGHT : {

		 	std::shared_ptr<Light> light_core = static_cast< std::shared_ptr<Light> > ( Light_core );
			Light* render_light = new Light( );
			render_light->set_transform( new_current_matrix );
			// TODO set other Values
			light_data_.push_back( render_light );
			break;
		}
		case Core::CoreType::GEOMETRY : {

		 	std::shared_ptr<Geometry> geometry_core = static_cast< std::shared_ptr<Geometry> > ( current_core );
			Geometry* render_geometry = new Geometry( geometry_core.get_geometry(), geometry_core.get_material );
			render_geometry->set_transform( new_current_matrix );
			geometry_data_.push_back( render_geometry );	
			break;
		}
		default: break;
	}
	std::list<Node*> current_children = current_node.get_children();
	for ( auto child : current_children ) {
		traverse_( child,  new_current_matrix );
	}
	
}


std::vector<Geometry*> const& get_geometry_data() const {
	return geometry_data_;
}


std::vector<Light*> const& get_light_data() const {
	return light_data_;
}

std::vector<Camera*> const& get_geometry_data() const {
	return camera_data_;
}
