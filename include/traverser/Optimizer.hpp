#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <vector>
#include <eigen2/Eigen/Eigen>
#include <memory>

class Geometry;
class Light;
class Camera;
class Node;
class SceneGraph;

class Optimizer {
    public:
        Optimizer();
        virtual ~Optimizer();
	
	void check( SceneGraph const* scene_graph );
	std::vector<Geometry*> const& get_geometry_data() const;
	std::vector<Light*> const& get_light_data() const;
	std::vector<Camera*> const& get_camera_data() const;	

	private:
        	std::vector<Geometry*> geometry_data_;
        	std::vector<Light*> light_data_;
        	std::vecotr<Camera*> camera_data_;
		void traverse_( Node* current_node, Eigen::Matrix4f current_matrix );  


};

#endif // OPTIMIZER_HPP
