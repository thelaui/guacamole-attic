#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <memory>
#include <eigen2/Eigen/Geometry>

#include "include/scenegraph/SceneGraph.hpp"

class SceneGraph::Node {
    public:
        Node(std::string const& name, Eigen::Transform3f transform = (Eigen::Transform3f)Eigen::Matrix3f::Identity(),
             Core* core = NULL);

        virtual ~Node();

        void add_child(Node* child);
        void remove_child(Node* child);

        Node* get_parent() const;
        std::list<Node*> const& get_children() const;

        std::string const& get_name() const;
        void set_name(std::string const& name);

        Eigen::Transform3f const& get_transform() const;
        void set_transform(Eigen::Transform3f const& transform);

        template <class T = Core>
        std::shared_ptr<T> const get_core() const {
            return std::static_pointer_cast<T>(core_);
        }



        void set_core(std::shared_ptr<Core> const& core);

        int get_depth() const;
        std::string const get_path() const;

    private:
        std::string name_;

        Node* parent_;
        std::list<Node*> children_;

        Eigen::Transform3f transform_;
        std::shared_ptr<Core> core_;
};


#endif //NODE_HPP
