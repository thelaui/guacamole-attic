#include "include/scenegraph/SceneGraph.hpp"

#include "include/scenegraph/Core.hpp"
#include "include/utils/PathParser.hpp"
#include "include/utils/debug.hpp"

//////////////////////////////////////////////////////////////////////////
///SceneGraph implementation
//////////////////////////////////////////////////////////////////////////

SceneGraph::SceneGraph():
    root_(new Node("/")) {}


SceneGraph::~SceneGraph() {
    delete root_;
}

void SceneGraph::add_node(std::string const& path_to_parent, std::string const& node_name,
                          Eigen::Matrix4f const& transform, Core* core) {
    Node* searched_parent(find_node(path_to_parent));

    if (searched_parent)
        searched_parent->add_child(new Node(node_name, transform, core));

}

SceneGraph::Node* SceneGraph::find_node(std::string const& path_to_node) const {
    PathParser parser;
    parser.parse(path_to_node);
    auto path_data(parser.get_parsed_path());

    Node* to_be_found(root_);

    for (auto node_name : path_data) {

        if (to_be_found->get_name() != node_name) {

            auto current_children(to_be_found->get_children());

            for (auto child : current_children) {
                if (child->get_name() == node_name) {
                    to_be_found = child;
                    break;
                }
            }

            if (to_be_found->get_name() != node_name) {
                WARNING("Node %s does not exist! Creating it with default parameters.",
                         node_name.c_str());
                to_be_found->add_child(new Node(node_name));
            }

        }
    }

    return to_be_found;
}


//////////////////////////////////////////////////////////////////////////
///Node implementation
//////////////////////////////////////////////////////////////////////////

SceneGraph::Node::Node(std::string const& name, Eigen::Matrix4f transform, Core* core):
    name_(name),
    parent_(NULL),
    children_(),
    transform_(transform),
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



