////////////////////////////////////////////////////////////////////////////////
// guacamole - an interesting scenegraph implementation
//
// Copyright (c) 2011 by Mischa Krempel, Felix Lauer and Simon Schneegans
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief A non-cyclic graph used as a powerfull tool to set up scenes.
////////////////////////////////////////////////////////////////////////////////

#include "scenegraph/SceneGraph.hpp"

#include "scenegraph/Iterator.hpp"
#include "scenegraph/Node.hpp"
#include "scenegraph/Core.hpp"
#include "utils/PathParser.hpp"
#include "utils/debug.hpp"

namespace gua {

SceneGraph::SceneGraph():
    root_(new Node("/")),
    working_node_(root_) {}

SceneGraph::SceneGraph(SceneGraph const& graph):
    root_(graph.root_ ? graph.root_->deep_copy() : NULL),
    working_node_(root_) {}

SceneGraph::~SceneGraph() {
    delete root_;
}

SceneGraph::Iterator SceneGraph::add_node(std::string const& path_to_parent, std::string const& node_name, Core* core,
                          math::mat4 const& transform) {

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
              math::mat4 const& transform) {

    Node* searched_parent(find_node(path_to_parent, working_node_->get_path(), true));
    if (searched_parent && !has_child(searched_parent, node_name)) {
        Node* new_node(new Node(node_name, transform, core));
        searched_parent->add_child(new_node);
        return Iterator(new_node);
    }

    WARNING("A node with the name %s already exists at %s!", node_name.c_str(), path_to_parent.c_str());
    return Iterator();
}

SceneGraph::Iterator SceneGraph::remove_node(std::string const& path_to_node) {
    Node* searched_node(find_node(path_to_node));
    Iterator it(searched_node);
    ++it;
    delete searched_node;
    return it;
}

SceneGraph::Iterator SceneGraph::move_node(std::string const& path_to_node, std::string const& path_to_target) {
    PathParser parser;
    parser.parse(path_to_target);

    Node* parent(find_node(path_to_target));
    Node* child(find_node(path_to_node));

    if (parser.path_is_finished_by_slash()) {
        if (child->get_parent())
            child->get_parent()->remove_child(child);
        parent->add_child(child);
        return Iterator(child);
    }

    if (child->get_parent())
        child->get_parent()->remove_child(child);

    Node* parents_parent(parent->get_parent());
    if (parents_parent) {
        parents_parent->remove_child(parent);
        parents_parent->add_child(child);
    }

    delete parent;
    parent = child;
    return Iterator(parent);
}

SceneGraph::Iterator SceneGraph::copy_node(std::string const& path_to_node, std::string const& path_to_target) {
    return Iterator();
}

void SceneGraph::set_working_node(std::string const& path_to_node) {
    working_node_ = find_node(path_to_node);
}

SceneGraph::Iterator SceneGraph::get_iterator(std::string const& path_to_node, IterationType type) const {
    return Iterator(find_node(path_to_node), type);
}

SceneGraph::Iterator SceneGraph::begin(IterationType type) const {
    auto root_children(root_->get_children());
    if (!root_children.empty())
        return Iterator(root_, type);
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

    Node* to_be_found(path_to_start == working_node_->get_name() ? working_node_ : find_node(path_to_start));

    for (auto const& node_name : parser.get_parsed_path()) {

        for (auto child : to_be_found->get_children()) {
            if (child->get_name() == node_name) {
                to_be_found = child;
                break;
            }
        }

        if (to_be_found->get_name() != node_name) {
            if (!add_missing_nodes) return NULL;

            MESSAGE("A node with the name %s does not exist! Creating it with default parameters.",
                    node_name.c_str());
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

}
