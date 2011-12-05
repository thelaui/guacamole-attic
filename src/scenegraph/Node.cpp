#include "include/scenegraph/Node.hpp"

#include "include/scenegraph/Core.hpp"

Node::Node(Core* core):
    parent_(NULL),
    children_(),
    core_(std::shared_ptr<Core>(core)) {}

Node::~Node() {
    if (parent_) {
        for (auto child : children_) {
            child->parent_ = parent_;
            parent_->add_child(child);
        }
    } else {
        for (auto child : children_) {
            child->parent_ = NULL;
            delete child;
        }
    }
}

void Node::add_child(Node* child) {
    children_.push_back(child);
    child->parent_ = this;
}

std::list<Node*> const& Node::get_children() const {
    return children_;
}

std::shared_ptr<Core> Node::get_core() const {
    return core_;
}
