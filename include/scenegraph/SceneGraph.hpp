#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include "include/scenegraph/Core.hpp"
#include "include/scenegraph/Node.hpp"

#include <list>
#include <memory>
#include <eigen2/Eigen/Geometry>

class GeometryCore;
class LightCore;
class CameraCore;

class SceneGraph {

    public:
        class Iterator {
            public:
                Iterator(Node* node = NULL);

                std::string name;
                Eigen::Transform3f transform;
                std::shared_ptr<Core> core;

                int depth;

                void operator ++();
                bool operator ==(Iterator const& rhs);
                bool operator !=(Iterator const& rhs);

            private:
                std::list<Node*> visited_nodes_;

                void find_next_node();
                void set_data(Node* node);
        };

    public:
        SceneGraph();

        virtual ~SceneGraph();

        void add_node(std::string const& path_to_parent, std::string const& node_name,
                      Eigen::Transform3f const& transform = (Eigen::Transform3f) Eigen::Transform3f::Identity(),
                      Core* core = NULL);

        Eigen::Transform3f const& get_transform(std::string const& path_to_node) const;
        Eigen::Transform3f get_relative_transform(std::string const& path_to_node,
                                                      std::string const& path_to_relative_node = "/") const;

        template <typename T>
        T* get_core(std::string const& path_to_node) const {
            Node* searched_node(find_node(path_to_node));
            Core* searched_core(searched_node->get_core());
            switch (searched_core->get_type()) {
                case Core::GEOMETRY: return reinterpret_cast<GeometryCore*>(searched_core);
                case Core::LIGHT: return reinterpret_cast<LightCore*>(searched_core);
                case Core::CAMERA: return reinterpret_cast<CameraCore*>(searched_core);
            }
        }

        Iterator get_iterator(std::string const& path_to_node);

        Iterator begin();
        Iterator end();

        void lock();
        void unlock();

    private:
        Node *root_;

        mutable std::string last_search_request_;
        mutable std::list<Node*> last_search_result_;

        Node* find_node(std::string const& path_to_node, std::string const& path_to_start = "/") const;


};


#endif // SCENE_GRAPH_HPP
