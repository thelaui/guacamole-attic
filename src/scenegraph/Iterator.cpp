#include "include/scenegraph/SceneGraph.hpp"

SceneGraph::Iterator::Iterator(Node* node):
    transform(node->get_transform()),
    core(node->get_core()),
    depth(0) {

        visited_nodes_.push_back(node);
    }

void SceneGraph::Iterator::operator ++() {
    Node* current_node(visited_nodes_.back());
    auto current_children(current_node->get_children());

    if (current_children.size() > 0) {
        visited_nodes_.push_back(current_children.front());
    } else {

        Node* last_visited_node(current_children.back());
        current_children.pop_back();
        for (auto child(current_children.begin()); child != current_children.end(); ++child)
            if (*child == last_visited_node) {
                if (++child != current_children.end()) {
                    visited_nodes_.push_back(*child);
                    break;
                } else {
                    if (visited_nodes_.size() > 1) {
                        visited_nodes_.pop_back();
                    }
                }
            }
    }

    depth = visited_nodes_.size()-1;
}

bool SceneGraph::Iterator::operator ==(Iterator const& rhs) {
    return visited_nodes_.back() == rhs.visited_nodes_.back();
}

bool SceneGraph::Iterator::operator !=(Iterator const& rhs) {
    return visited_nodes_.back() != rhs.visited_nodes_.back();
}
