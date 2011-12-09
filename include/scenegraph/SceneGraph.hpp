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

                std::string& name();
                Eigen::Transform3f& transform();
                std::shared_ptr<Core> core();

                int depth;

                void operator ++();
                bool operator ==(Iterator const& rhs);
                bool operator !=(Iterator const& rhs);

            private:
                std::string name_;
                Eigen::Transform3f transform_;
                std::shared_ptr<Core> core_;

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
        std::shared_ptr<T> get_core(std::string const& path_to_node) const {
            Node* searched_node(find_node(path_to_node));
            std::shared_ptr<Core> searched_core(searched_node->get_core());
            return std::static_pointer_cast<T>(searched_core);
        }

        Iterator get_iterator(std::string const& path_to_node);

        Iterator begin();
        Iterator end();

        Iterator operator [](std::string const& path_to_node);

        void lock();
        void unlock();

    private:
        Node *root_;

        mutable std::string last_search_request_;
        mutable std::list<Node*> last_search_result_;

        Node* find_node(std::string const& path_to_node, std::string const& path_to_start = "/") const;


};


#endif // SCENE_GRAPH_HPP
