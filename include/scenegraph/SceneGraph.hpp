#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include "include/scenegraph/Core.hpp"

#include <list>
#include <eigen2/Eigen/Geometry>

class GeometryCore;
class LightCore;
class CameraCore;

class SceneGraph {

    public: class Iterator;
    private: class Node;

    public:
        SceneGraph();

        virtual ~SceneGraph();

        Iterator add_node(std::string const& path_to_parent, std::string const& node_name,
                      Eigen::Transform3f const& transform = (Eigen::Transform3f) Eigen::Transform3f::Identity(),
                      Core* core = NULL);

        Iterator add_node_recursively(std::string const& path_to_parent, std::string const& node_name,
                      Eigen::Transform3f const& transform = (Eigen::Transform3f) Eigen::Transform3f::Identity(),
                      Core* core = NULL);


        void remove_node(std::string const& path_to_node);

        void set_working_node(std::string const& path_to_node);

        Iterator get_iterator(std::string const& path_to_node);

        Iterator begin();
        Iterator end();

        Iterator operator [](std::string const& path_to_node);

        void lock();
        void unlock();

    private:
        Node *root_, *working_node_;

        Node* find_node(std::string const& path_to_node, std::string const& path_to_start = "/",
                        bool add_missing_nodes = false) const;

        bool has_child(Node* parent, std::string const& child_name) const;
};


#endif // SCENE_GRAPH_HPP
