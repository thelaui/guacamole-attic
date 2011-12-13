#include "include/scenegraph/Iterator.hpp"
#include "include/scenegraph/Node.hpp"
#include "include/utils/debug.hpp"

const std::string SceneGraph::Iterator::end_name_("end");
const Eigen::Transform3f SceneGraph::Iterator::end_transform_((Eigen::Transform3f)Eigen::Matrix3f::Identity());

SceneGraph::Iterator::Iterator(Node* node):
    current_node_(node),
    start_node_(node) {}

int SceneGraph::Iterator::get_depth() const {
    if (current_node_) return current_node_->get_depth();
    return 0;
}

std::string const& SceneGraph::Iterator::get_name() const {
    if (current_node_) return current_node_->get_name();
    return end_name_;
}

void SceneGraph::Iterator::set_name(std::string const& name) const {
    if (current_node_) {
        if (current_node_->get_name() == "/")
            WARNING("You are trying to set the name of the root node, which is not allowed!");
        else current_node_->set_name(name);
    }
}

Eigen::Transform3f const& SceneGraph::Iterator::get_transform() const {
    if (current_node_) return current_node_->get_transform();
    return end_transform_;
}

void SceneGraph::Iterator::set_transform(Eigen::Transform3f const& transform) const {
    if (current_node_) current_node_->set_transform(transform);
}

void SceneGraph::Iterator::set_core(Core* core) const {
    if (current_node_) current_node_->set_core(core);
}

void SceneGraph::Iterator::scale(double x, double y, double z) {
    if (current_node_) current_node_->scale(x, y, z);
}

void SceneGraph::Iterator::rotate(double angle, double x, double y, double z) {
    if (current_node_) current_node_->rotate(angle, x, y, z);
}

void SceneGraph::Iterator::translate(double x, double y, double z) {
    if (current_node_) current_node_->translate(x, y, z);
}

void SceneGraph::Iterator::operator ++() {
    auto current_children(current_node_->get_children());

    if (!current_children.empty()) {
        Node* next_node(current_children.front());
        current_node_ = next_node;
    } else find_next_node();
}

bool SceneGraph::Iterator::operator ==(Iterator const& rhs) {
    return (current_node_ == rhs.current_node_);
}

bool SceneGraph::Iterator::operator !=(Iterator const& rhs) {
    return (current_node_ != rhs.current_node_);
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (std::string const& name) {
    set_name(name);
    return *this;
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (Eigen::Transform3f const& transform) {
    set_transform(transform);
    return *this;
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (Core* core) {
    set_core(core);
    return *this;
}

void SceneGraph::Iterator::find_next_node() {
    bool found_next(false);
    while (!found_next) {
        Node* current_parent(current_node_->get_parent());

        if (current_node_ != start_node_) {
            auto previous_children(current_parent->get_children());
            for (auto child(previous_children.begin()); child != previous_children.end(); ++child) {
                if (*child == current_node_) {
                    if (++child != previous_children.end()) {
                        current_node_ = *child;
                        found_next = true;
                        break;
                    } else {
                        current_node_ = current_parent;
                        break;
                    }
                }
            }
        } else {
            *this = Iterator();
            break;
        }
    }
}