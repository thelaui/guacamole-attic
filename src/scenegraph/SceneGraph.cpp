#include "include/scenegraph/SceneGraph.hpp"

#include "include/scenegraph/Core.hpp"

//////////////////////////////////////////////////////////////////////////
///SceneGraph implementation
//////////////////////////////////////////////////////////////////////////

SceneGraph::SceneGraph():
    root_(new Node("root", NULL)) {}


SceneGraph::~SceneGraph() {
    delete root_;
}

//////////////////////////////////////////////////////////////////////////
///Node implementation
//////////////////////////////////////////////////////////////////////////

SceneGraph::Node::Node(std::string const& name, Core* core):
    name_(name),
    parent_(NULL),
    children_(),
    core_(std::shared_ptr<Core>(core)) {}

SceneGraph::Node::~Node() {
    if (parent_)
        parent_->remove_child(this);

    for (auto child : children_) {
        child->parent_ = NULL;
        delete child;
    }
}

void SceneGraph::Node::add_child(Node* child) {
    children_.push_back(child);
    child->parent_ = this;
}

void SceneGraph::Node::remove_child(Node* child) {
    children_.remove(child);
}

std::string const& SceneGraph::Node::get_name() const {
    return name_;
}

std::list<SceneGraph::Node*> const& SceneGraph::Node::get_children() const {
    return children_;
}

Eigen::Matrix4f const& SceneGraph::Node::get_transform() const {
    return transform_;
}

std::shared_ptr<Core> SceneGraph::Node::get_core() const {
    return core_;
}


