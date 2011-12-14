#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <vector>
#include <memory>

class GeometryNode;
class LightNode;
class CameraNode;

class SceneGraph;

class Optimizer {
    public:
        Optimizer();
        virtual ~Optimizer();
	
		void check( SceneGraph const* scene_graph );
		std::vector<GeometryNode*> const& get_geometry_data() const;
		std::vector<LightNode*> const& get_light_data() const;
		std::vector<CameraNode*> const& get_camera_data() const;	

	private:
		std::vector<GeometryNode*> geometry_data_;
		std::vector<LightNode*> light_data_;
		std::vector<CameraNode*> camera_data_;

};

#endif // OPTIMIZER_HPP
