#include "include/scenegraph/SceneGraph.hpp"

SceneGraph::Iterator::Iterator(Node* node):
    depth(0),
    name_(node ? node->get_name() : "end"),
    transform_(node ? node->get_transform() : (Eigen::Transform3f)Eigen::Transform3f::Identity()),
    core_(node ? node->get_core() : NULL) {
        if (node)
            visited_nodes_.push_back(node);
    }

std::string& SceneGraph::Iterator::name() {
    return visited_nodes_.back()->get_name();
}

Eigen::Transform3f& SceneGraph::Iterator::transform() {
    return visited_nodes_.back()->get_transform();
}

std::shared_ptr<Core> SceneGraph::Iterator::core() {
    return visited_nodes_.back()->get_core();
}

void SceneGraph::Iterator::operator ++() {
    if (!visited_nodes_.empty()) {
        Node* current_node(visited_nodes_.back());
        auto current_children(current_node->get_children());

        if (!current_children.empty()) {
            Node* next_node(current_children.front());
            set_data(next_node);
            visited_nodes_.push_back(next_node);

        } else find_next_node();

        depth = visited_nodes_.size()-1;
    }
}

bool SceneGraph::Iterator::operator ==(Iterator const& rhs) {
    return name_ == rhs.name_;
}

bool SceneGraph::Iterator::operator !=(Iterator const& rhs) {
    return name_ != rhs.name_;
}

void SceneGraph::Iterator::find_next_node() {
    bool found_next(false);
    while (!found_next) {
        Node* last_visited_node(visited_nodes_.back());
        visited_nodes_.pop_back();

        if (!visited_nodes_.empty()) {
            auto previous_children(visited_nodes_.back()->get_children());
            for (auto child(previous_children.begin()); child != previous_children.end(); ++child) {
                if (*child == last_visited_node) {
                    if (++child != previous_children.end()) {
                        visited_nodes_.push_back(*child);
                        set_data(*child);
                        found_next = true;
                        break;
                    } else break;
                }
            }
        } else {
            *this = Iterator();
            break;
        }
    }
}

void SceneGraph::Iterator::set_data(Node* node) {
    name_ = node->get_name();
    transform_ = node->get_transform();
    core_ = node->get_core();
}
