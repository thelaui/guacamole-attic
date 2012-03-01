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
/// \brief A simple structure used to store and organize SceneGraph data.
////////////////////////////////////////////////////////////////////////////////

#include "scenegraph/Node.hpp"
#include "scenegraph/Core.hpp"

namespace gua {

SceneGraph::Node::Node(std::string const& name, math::mat4 transform,
                       Core* core, InheritanceMode mode):
    name_(name),
    parent_(NULL),
    children_(),
    private_transform_(mode == PUBLIC ? math::mat4::identity() : transform),
    public_transform_(mode == PRIVATE ? math::mat4::identity() : transform),
    core_(core) {}

SceneGraph::Node::~Node() {
    if (parent_)
        parent_->remove_child(this);

    for (auto child : children_) {
        child->parent_ = NULL;
        delete child;
    }
}

void SceneGraph::Node::add_child(SceneGraph::Node* child) {
    children_.push_back(child);
    child->parent_ = this;
}

void SceneGraph::Node::remove_child(SceneGraph::Node* child) {
    child->parent_ = NULL;
    children_.remove(child);
}

std::list<SceneGraph::Node*> const& SceneGraph::Node::get_children() const {
    return children_;
}

SceneGraph::Node* SceneGraph::Node::get_parent() const {
    return parent_;
}

void SceneGraph::Node::set_parent(SceneGraph::Node* parent) {
    parent_ = parent;
}

std::string const& SceneGraph::Node::get_name() const {
    return name_;
}

void SceneGraph::Node::set_name(std::string const& name) {
    name_ = name;
}

math::mat4 const& SceneGraph::Node::get_transform(InheritanceMode mode) const {
    if (mode == PUBLIC)
        return public_transform_;

    return private_transform_;
}

void SceneGraph::Node::set_transform(math::mat4 const& transform, InheritanceMode mode) {
    if (mode == PUBLIC) public_transform_ = transform;
    else private_transform_ = transform;
}

Core* SceneGraph::Node::get_core() const {
    return core_;
}

void SceneGraph::Node::set_core(Core* core) {
    core_ = core;
}

void SceneGraph::Node::scale(float x, float y, float z,
                             TransformMode transform_mode,
                             InheritanceMode inheritance_mode) {

    math::mat4 scale(scm::math::make_scale(x, y, z));

    if (inheritance_mode == PUBLIC) {
        if (transform_mode == GLOBAL) {
            public_transform_ = scale * public_transform_;
            private_transform_ = scale * private_transform_;
        } else {
            public_transform_ =  public_transform_ * scale;
            private_transform_ = private_transform_ * scale;
        }
    } else {
        if (transform_mode == GLOBAL) {
            private_transform_ = scale * private_transform_;
        } else {
            private_transform_ = private_transform_ * scale;
        }
    }
}

void SceneGraph::Node::rotate(float angle, float x, float y, float z,
                              TransformMode transform_mode,
                              InheritanceMode inheritance_mode) {

    math::mat4 rotation(scm::math::make_rotation(angle, x, y, z));

    if (inheritance_mode == PUBLIC) {
        if (transform_mode == GLOBAL) {
            public_transform_ = rotation * public_transform_;
            private_transform_ = rotation * private_transform_;
        } else {
            public_transform_ =  public_transform_ * rotation;
            private_transform_ = private_transform_ * rotation;
        }
    } else {
        if (transform_mode == GLOBAL) {
            private_transform_ = rotation * private_transform_;
        } else {
            private_transform_ = private_transform_ * rotation;
        }
    }
}

void SceneGraph::Node::translate(float x, float y, float z,
                                 TransformMode transform_mode,
                                 InheritanceMode inheritance_mode) {

    math::mat4 translation(scm::math::make_translation(x, y, z));

    if (inheritance_mode == PUBLIC) {
        if (transform_mode == GLOBAL) {
            public_transform_ = translation * public_transform_;
            private_transform_ = translation * private_transform_;
        } else {
            public_transform_ =  public_transform_ * translation;
            private_transform_ = private_transform_ * translation;
        }
    } else {
        if (transform_mode == GLOBAL) {
            private_transform_ = translation * private_transform_;
        } else {
            private_transform_ = private_transform_ * translation;
        }
    }
}

int SceneGraph::Node::get_depth() const {
    if (!parent_) return 0;
    return parent_->get_depth() + 1;
}

std::string const SceneGraph::Node::get_path() const {
    if (!parent_) return "/";
    return parent_->get_path() + "/" + name_;
}

}
