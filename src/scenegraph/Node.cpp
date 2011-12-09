#include "include/scenegraph/Node.hpp"
#include "include/scenegraph/Core.hpp"

Node::Node(std::string const& name, Eigen::Transform3f transform, Core* core):
    name_(name),
    parent_(NULL),
    children_(),
    transform_(transform),
    core_(std::shared_ptr<Core>(core)) {}

Node::~Node() {
    if (parent_)
        parent_->remove_child(this);

    for (auto child : children_) {
        child->parent_ = NULL;
        delete child;
    }
}

void Node::add_child(Node* child) {
    children_.push_back(child);
    child->parent_ = this;
}

void Node::remove_child(Node* child) {
    children_.remove(child);
}

std::string const& Node::get_name() const {
    return name_;
}

std::list<Node*> const& Node::get_children() const {
    return children_;
}

Node* Node::get_parent() const {
    return parent_;
}

Eigen::Transform3f const& Node::get_transform() const {
    return transform_;
}

std::shared_ptr<Core> Node::get_core() const {
    return core_;
}
