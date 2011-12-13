#include "include/scenegraph/Node.hpp"
#include "include/scenegraph/Core.hpp"

SceneGraph::Node::Node(std::string const& name, Eigen::Transform3f transform, Core* core):
    name_(name),
    parent_(NULL),
    children_(),
    transform_(transform),
    core_(core) {}

SceneGraph::Node::~Node() {
    if (parent_)
        parent_->remove_child(this);

    for (auto child : children_) {
        child->parent_ = NULL;
        delete child;
    }
}

void SceneGraph::Node::add_child(SceneGraph::Node* child) {
    children_.push_back(child);
    child->parent_ = this;
}

void SceneGraph::Node::remove_child(SceneGraph::Node* child) {
    children_.remove(child);
}

std::list<SceneGraph::Node*> const& SceneGraph::Node::get_children() const {
    return children_;
}

SceneGraph::Node* SceneGraph::Node::get_parent() const {
    return parent_;
}

std::string const& SceneGraph::Node::get_name() const {
    return name_;
}

void SceneGraph::Node::set_name(std::string const& name) {
    name_ = name;
}

Eigen::Transform3f const& SceneGraph::Node::get_transform() const {
    return transform_;
}

void SceneGraph::Node::set_transform(Eigen::Transform3f const& transform) {
    transform_ = transform;
}

void SceneGraph::Node::set_core(Core* core) {
    core_ = core;
}

void SceneGraph::Node::scale(double x, double y, double z) {
    transform_.scale(Eigen::Vector3f(x, y, z));
}

void SceneGraph::Node::rotate(double angle, double x, double y, double z) {
    transform_.rotate(Eigen::AngleAxisf(angle, Eigen::Vector3f(x, y, z)));
}

void SceneGraph::Node::translate(double x, double y, double z) {
    transform_.translate(Eigen::Vector3f(x, y, z));
}

int SceneGraph::Node::get_depth() const {
    if (!parent_) return 0;
    return parent_->get_depth() + 1;
}

std::string const SceneGraph::Node::get_path() const {
    if (!parent_) return "/";
    return parent_->get_path() + "/" + name_;
}
