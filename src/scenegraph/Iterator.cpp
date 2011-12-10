#include "include/scenegraph/SceneGraph.hpp"
#include "include/utils/debug.hpp"

SceneGraph::Iterator::Iterator(Node* node):
    depth_(0),
    name_(node ? node->get_name() : "end"),
    transform_(node ? node->get_transform() : (Eigen::Transform3f)Eigen::Transform3f::Identity()),
    core_(node ? node->get_core() : NULL) {
        if (node)
            visited_nodes_.push_back(node);
    }

int SceneGraph::Iterator::depth() const {
    return depth_;
}

std::string& SceneGraph::Iterator::name() {
    if (visited_nodes_.back()->get_name() == "/") {
        WARNING("You are trying to change the name of root, which is is not allowed. Returning non-persistent name instead.");
        return name_;
    }
    return visited_nodes_.back()->get_name();
}

std::string const& SceneGraph::Iterator::name() const{
    return name_;
}

Eigen::Transform3f& SceneGraph::Iterator::transform() {
    return visited_nodes_.back()->get_transform();
}

Eigen::Transform3f const& SceneGraph::Iterator::transform() const{
    return transform_;
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

        depth_ = visited_nodes_.size()-1;
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
