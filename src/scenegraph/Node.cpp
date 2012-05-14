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
/// \brief A simple structure used to store and organize SceneGraph data.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "scenegraph/Node.hpp"

// guacamole headers
#include "scenegraph/Core.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////
SceneGraph::Node::
Node(std::string const& name, math::mat4 transform, Core* core):
    name_(name),
    parent_(NULL),
    children_(),
    transform_(transform),
    core_(core) {}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Node::
~Node() {

    if (parent_)
        parent_->remove_child(this);

    for (auto child : children_) {
        child->parent_ = NULL;
        delete child;
    }
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
add_child(SceneGraph::Node* child) {

    children_.push_back(child);
    child->parent_ = this;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
remove_child(SceneGraph::Node* child) {

    child->parent_ = NULL;
    children_.remove(child);
}

////////////////////////////////////////////////////////////////////////////////

std::list<SceneGraph::Node*> const& SceneGraph::Node::
get_children() const {

    return children_;
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Node* SceneGraph::Node::
get_parent() const {

    return parent_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
set_parent(SceneGraph::Node* parent) {

    parent_ = parent;
}

////////////////////////////////////////////////////////////////////////////////

std::string const& SceneGraph::Node::
get_name() const {

    return name_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
set_name(std::string const& name) {

    name_ = name;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
add_to_group(std::string const& group) {

    group_list_.insert(group);
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
add_to_groups(std::set<std::string> const& groups) {

    group_list_.insert(groups.begin(), groups.end());
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
remove_from_group(std::string const& group) {

    group_list_.erase(group);
}

////////////////////////////////////////////////////////////////////////////////

bool SceneGraph::Node::
is_in_group(std::string const& group) const {

    return group_list_.find(group) != group_list_.end();
}

////////////////////////////////////////////////////////////////////////////////

std::set<std::string> const& SceneGraph::Node::
get_groups() const {

    return group_list_;
}

////////////////////////////////////////////////////////////////////////////////

math::mat4 const& SceneGraph::Node::
get_transform() const {

    return transform_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
set_transform(math::mat4 const& transform) {

    transform_ = transform;
}

////////////////////////////////////////////////////////////////////////////////

Core* SceneGraph::Node::
get_core() const {

    return core_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
set_core(Core* core) {

    core_ = core;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
scale(float x, float y, float z) {

    transform_ = scm::math::make_scale(x, y, z) * transform_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
rotate(float angle, float x, float y, float z) {

    transform_ = scm::math::make_rotation(angle, x, y, z) * transform_;
}

////////////////////////////////////////////////////////////////////////////////

void SceneGraph::Node::
translate(float x, float y, float z) {

    transform_ = scm::math::make_translation(x, y, z) * transform_;
}

////////////////////////////////////////////////////////////////////////////////

int SceneGraph::Node::
get_depth() const {

    if (!parent_) return 0;
    return parent_->get_depth() + 1;
}

////////////////////////////////////////////////////////////////////////////////

std::string const SceneGraph::Node::
get_path() const {

    if (!parent_) return "/";
    return parent_->get_path() + "/" + name_;
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph::Node* SceneGraph::Node::
deep_copy() const {

    Node* copy = new Node(name_, transform_, core_);
    copy->add_to_groups(group_list_);

    for (auto child: children_)
        copy->add_child(child->deep_copy());

    return copy;
}

////////////////////////////////////////////////////////////////////////////////

}
