////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
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
/// \brief An Iterator to get access to Nodes without having to touch them
///        directly.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "scenegraph/Iterator.hpp"

// guacamole headers
#include "scenegraph/Node.hpp"
#include "utils/Profiler.hpp"
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

const std::string SceneGraph::Iterator::end_name_("end");
const math::mat4 SceneGraph::Iterator::end_transform_(math::mat4::identity());

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Iterator::
Iterator(Node* node, IterationType type):
    current_node_(node),
    start_node_(node),
    type_(type),
    breadth_nodes_(),
    current_depth_(0) {}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Iterator SceneGraph::Iterator::
add_child(std::string const& node_name, Core* core,
          math::mat4 const& transform) const{

    Node* new_node(new Node(node_name, transform, core));
    current_node_->add_child(new_node);
    return Iterator(new_node);
}

////////////////////////////////////////////////////////////////////////////////

int SceneGraph::Iterator::
get_depth() const {

    if (current_node_) return current_node_->get_depth();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

std::string const& SceneGraph::Iterator::
get_name() const {

    if (current_node_) return current_node_->get_name();
    return end_name_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
set_name(std::string const& name) const {

    if (current_node_) {
        if (current_node_->get_name() == "/")
            WARNING("You are trying to set the name of the root node, which"
                    " is not allowed!");
        else current_node_->set_name(name);
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
add_to_group(std::string const& group) {

    if (current_node_)
        current_node_->add_to_group(group);
}

void SceneGraph::Iterator::
add_to_groups(std::vector<std::string> const& groups) {

    if (current_node_)
        current_node_->add_to_groups(groups);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
remove_from_group(std::string const& group) {

    if (current_node_)
        current_node_->remove_from_group(group);
}

////////////////////////////////////////////////////////////////////////////////

bool SceneGraph::Iterator::
is_in_group(std::string const& group) const {

    if (current_node_)
        return current_node_->is_in_group(group);
    return false;
}

////////////////////////////////////////////////////////////////////////////////

std::set<std::string> const& SceneGraph::Iterator::
get_groups() const {

    if (!current_node_)
        ERROR("Failed to get groups of node: Invalid iterator!");
    return current_node_->get_groups();
}

////////////////////////////////////////////////////////////////////////////////

math::mat4 const& SceneGraph::Iterator::
get_transform() const {

    if (current_node_) return current_node_->get_transform();
    return end_transform_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
set_transform(math::mat4 const& transform) const {

    if (current_node_) current_node_->set_transform(transform);
}

////////////////////////////////////////////////////////////////////////////////

Core* SceneGraph::Iterator::
get_core() const {

    if (current_node_)
        return current_node_->get_core();
    return NULL;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
set_core(Core* core) const {

    if (current_node_) current_node_->set_core(core);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
scale(double x, double y, double z) {

    if (current_node_) current_node_->scale(x, y, z);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
rotate(double angle, double x, double y, double z) {

    if (current_node_) current_node_->rotate(angle, x, y, z);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
translate(double x, double y, double z) {

    if (current_node_) current_node_->translate(x, y, z);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
set_iteration_type(IterationType type) {

    type_ = type;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
operator ++() {

    switch (type_) {
        case SceneGraph::DEPTH_FIRST:
            find_next_node_depth();
            break;
        case SceneGraph::BREADTH_FIRST:
            find_next_node_breadth();
            break;
        default: break;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool SceneGraph::Iterator::
operator ==(Iterator const& rhs) {

    return (current_node_ == rhs.current_node_);
}

////////////////////////////////////////////////////////////////////////////////

bool SceneGraph::Iterator::
operator !=(Iterator const& rhs) {

    return (current_node_ != rhs.current_node_);
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Iterator& SceneGraph::Iterator::
operator << (std::string const& name) {

    set_name(name);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Iterator& SceneGraph::Iterator::
operator << (math::mat4 const& transform) {

    set_transform(transform);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Iterator& SceneGraph::Iterator::
operator << (Core* core) {

    set_core(core);
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
find_next_node_depth() {

    if (!current_node_->get_children().empty()) {
        current_node_ = current_node_->get_children().front();
        ++current_depth_;
    } else {
        bool found_next(false);
        while (!found_next) {
            if (current_node_ != start_node_) {
                auto neighbour(get_neighbour(current_node_));
                if (neighbour) {
                    current_node_ = neighbour;
                    found_next = true;
                } else {
                    current_node_ = current_node_->get_parent();
                    --current_depth_;
                }
            } else {
                *this = Iterator();
                break;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Iterator::
find_next_node_breadth() {

    if (breadth_nodes_.empty()) {
        Iterator end;
        for (Iterator it(start_node_); it != end; ++it)
            breadth_nodes_[it.get_depth()].push_back(it.current_node_);
    }

    auto end(breadth_nodes_[current_depth_].end());
    for (auto node(breadth_nodes_[current_depth_].begin());
              node != end; ++node) {

        if (*node == current_node_) {
            if (++node != end) {
                current_node_ = *node;
            } else if (++current_depth_ < breadth_nodes_.size()) {
                current_node_ = breadth_nodes_[current_depth_].front();
            } else *this = Iterator();
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

gua::SceneGraph::Node* SceneGraph::Iterator::
get_neighbour(Node* to_be_checked) {

    auto end(to_be_checked->get_parent()->get_children().end());
    for (auto child(to_be_checked->get_parent()->get_children().begin());
              child != end; ++child) {

        if (*child == to_be_checked) {
            if (++child != end) {
                return *child;
            } else break;
        }
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////

}
