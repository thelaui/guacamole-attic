#include "include/scenegraph/SceneGraph.hpp"

#include "include/scenegraph/Iterator.hpp"
#include "include/scenegraph/Node.hpp"
#include "include/scenegraph/Core.hpp"
#include "include/utils/PathParser.hpp"
#include "include/utils/debug.hpp"

SceneGraph::SceneGraph():
    root_(new Node("/")),
    working_node_(root_) {}


SceneGraph::~SceneGraph() {
    delete root_;
}

SceneGraph::Iterator SceneGraph::add_node(std::string const& path_to_parent, std::string const& node_name, Core* core,
                          Eigen::Transform3f const& transform) {

    Node* searched_parent(find_node(path_to_parent));
    if (!searched_parent) {
        WARNING("A node with the name %s does not exist!", path_to_parent.c_str());
        return Iterator();
    }

    if (has_child(searched_parent, node_name)) {
        WARNING("A node with the name %s already exists at %s!", node_name.c_str(), path_to_parent.c_str());
        return Iterator();
    }

    Node* new_node(new Node(node_name, transform, core));
    searched_parent->add_child(new_node);
    return Iterator(new_node);
}

SceneGraph::Iterator SceneGraph::add_node_recursively(std::string const& path_to_parent, std::string const& node_name, Core* core,
              Eigen::Transform3f const& transform) {

    Node* searched_parent(find_node(path_to_parent, working_node_->get_path(), true));
    if (searched_parent && !has_child(searched_parent, node_name)) {
        Node* new_node(new Node(node_name, transform, core));
        searched_parent->add_child(new_node);
        return Iterator(new_node);
    }

    WARNING("A node with the name %s already exists at %s!", node_name.c_str(), path_to_parent.c_str());
    return Iterator();
}

void SceneGraph::remove_node(std::string const& path_to_node) {
    Node* searched_node(find_node(path_to_node));
    delete searched_node;
}

void SceneGraph::set_working_node(std::string const& path_to_node) {
    working_node_ = find_node(path_to_node);
}

SceneGraph::Iterator SceneGraph::get_iterator(std::string const& path_to_node) {
    return Iterator(find_node(path_to_node));
}

SceneGraph::Iterator SceneGraph::begin() const {
    auto root_children(root_->get_children());
    if (!root_children.empty())
        return Iterator(root_);
    else {
        WARNING("You are trying to iterate over an empty graph! Returning iterator on end.");
        return end();
    }
}

SceneGraph::Iterator SceneGraph::end() const {
    return Iterator();
}

SceneGraph::Iterator SceneGraph::operator [](std::string const& path_to_node) {
    return Iterator(find_node(path_to_node, working_node_->get_path(), true));
}

SceneGraph::Node* SceneGraph::find_node(std::string const& path_to_node, std::string const& path_to_start,
                                        bool add_missing_nodes) const {

    PathParser parser;
    parser.parse(path_to_node);
    auto path_data(parser.get_parsed_path());

    Node* to_be_found(path_to_start == working_node_->get_name() ? working_node_ : find_node(path_to_start));

    for (auto node_name : path_data) {

        for (auto child : to_be_found->get_children()) {
            if (child->get_name() == node_name) {
                to_be_found = child;
                break;
            }
        }

        if (to_be_found->get_name() != node_name) {
            if (!add_missing_nodes) return NULL;

            Node* new_child(new Node(node_name));
            to_be_found->add_child(new_child);
            to_be_found = new_child;
        }
    }

    return to_be_found;
}

bool SceneGraph::has_child(Node* parent, std::string const& child_name) const {
    auto children(parent->get_children());
    for (auto child : children)
        if (child->get_name() == child_name) {
            return true;
        }
    return false;
}

std::ostream& operator<<(std::ostream& os, SceneGraph const& graph) {
    for (SceneGraph::Iterator it(graph.begin()); it!=graph.end(); ++it) {
        for (int i(0); i<it.get_depth(); ++i)
            os << "  ";
        os << it.get_name() << std::endl;
    }
    return os;
}
