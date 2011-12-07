#ifndef SCENE_GRAPH_HPP
#define SCENE_GRAPH_HPP

#include <list>
#include <memory>
#include <eigen2/Eigen/Eigen>

class Core;

class SceneGraph {
    public:
        SceneGraph();
        virtual ~SceneGraph();

        void add_node(std::string const& path_to_parent, std::string const& node_name,
                      Eigen::Matrix4f const& transform = Eigen::Matrix4f::Identity(),
                      Core* core = NULL);

        Eigen::Matrix4f const& get_transform(std::string const& path_to_node) const;
        Eigen::Matrix4f const& get_relative_transform(std::string const& path_to_node,
                                                      std::string const& path_to_relative_node = "/") const;

        template <typename T>
        T* get_core(std::string const& path_to_node) const {

        }



        void lock();
        void unlock();

    private:
        class Node {
            public:
                Node(std::string const& name, Eigen::Matrix4f transform = Eigen::Matrix4f::Identity(),
                     Core* core = NULL);
                virtual ~Node();

                void add_child(Node* child);
                void remove_child(Node* child);

                std::string const& get_name() const;
                std::list<Node*> const& get_children() const;

                Eigen::Matrix4f const& get_transform() const;
                std::shared_ptr<Core> get_core() const;

            private:
                std::string name_;

                Node* parent_;
                std::list<Node*> children_;

                Eigen::Matrix4f transform_;
                std::shared_ptr<Core> core_;
        };

        Node* root_;

        Node* find_node(std::string const& path_to_node) const;


};

#endif // SCENE_GRAPH_HPP
