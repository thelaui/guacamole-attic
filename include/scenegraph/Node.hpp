#ifndef NODE_HPP
#define NODE_HPP

#include <memory>
#include <list>
#include <eigen2/Eigen/Geometry>

class Core;

class Node {
    public:
        Node(std::string const& name, Eigen::Transform3f transform = (Eigen::Transform3f)Eigen::Matrix3f::Identity(),
             Core* core = NULL);

        virtual ~Node();

        void add_child(Node* child);
        void remove_child(Node* child);

        std::string const& get_name() const;
        std::list<Node*> const& get_children() const;

        Eigen::Transform3f const& get_transform() const;
        std::shared_ptr<Core> get_core() const;

    private:
        std::string name_;

        Node* parent_;
        std::list<Node*> children_;

        Eigen::Transform3f transform_;
        std::shared_ptr<Core> core_;
};


#endif //NODE_HPP
