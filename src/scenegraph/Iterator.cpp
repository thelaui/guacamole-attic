#include "include/scenegraph/SceneGraph.hpp"

SceneGraph::Iterator::Iterator(Node* node):
    name(node ? node->get_name() : "end"),
    transform(node ? node->get_transform() : (Eigen::Transform3f)Eigen::Transform3f::Identity()),
    core(node ? node->get_core() : NULL),
    depth(0) {
        if (node)
            visited_nodes_.push_back(node);
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
    return name == rhs.name;
}

bool SceneGraph::Iterator::operator !=(Iterator const& rhs) {
    return name != rhs.name;
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
    name = node->get_name();
    transform = node->get_transform();
    core = node->get_core();
}
