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
/// \brief An Iterator to get access to Nodes without having to touch them
///        directly.
////////////////////////////////////////////////////////////////////////////////

#include "scenegraph/Iterator.hpp"
#include "scenegraph/Node.hpp"
#include "utils/debug.hpp"

namespace gua {

const std::string SceneGraph::Iterator::end_name_("end");
const Eigen::Transform3f SceneGraph::Iterator::end_transform_((Eigen::Transform3f)Eigen::Matrix3f::Identity());

SceneGraph::Iterator::Iterator(Node* node, IterationType type):
    current_node_(node),
    start_node_(node),
    type_(type) {}

int SceneGraph::Iterator::get_depth() const {
    if (current_node_) return current_node_->get_depth();
    return 0;
}

std::string const& SceneGraph::Iterator::get_name() const {
    if (current_node_) return current_node_->get_name();
    return end_name_;
}

void SceneGraph::Iterator::set_name(std::string const& name) const {
    if (current_node_) {
        if (current_node_->get_name() == "/")
            WARNING("You are trying to set the name of the root node, which is not allowed!");
        else current_node_->set_name(name);
    }
}

Eigen::Transform3f const& SceneGraph::Iterator::get_transform() const {
    if (current_node_) return current_node_->get_transform();
    return end_transform_;
}

void SceneGraph::Iterator::set_transform(Eigen::Transform3f const& transform) const {
    if (current_node_) current_node_->set_transform(transform);
}

Core* SceneGraph::Iterator::get_core() const {
    if (current_node_)
        return current_node_->get_core();
    return NULL;
}

void SceneGraph::Iterator::set_core(Core* core) const {
    if (current_node_) current_node_->set_core(core);
}

void SceneGraph::Iterator::scale(double x, double y, double z) {
    if (current_node_) current_node_->scale(x, y, z);
}

void SceneGraph::Iterator::rotate(double angle, double x, double y, double z) {
    if (current_node_) current_node_->rotate(angle, x, y, z);
}

void SceneGraph::Iterator::translate(double x, double y, double z) {
    if (current_node_) current_node_->translate(x, y, z);
}

void SceneGraph::Iterator::operator ++() {
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

bool SceneGraph::Iterator::operator ==(Iterator const& rhs) {
    return (current_node_ == rhs.current_node_);
}

bool SceneGraph::Iterator::operator !=(Iterator const& rhs) {
    return (current_node_ != rhs.current_node_);
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (std::string const& name) {
    set_name(name);
    return *this;
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (Eigen::Transform3f const& transform) {
    set_transform(transform);
    return *this;
}

SceneGraph::Iterator& SceneGraph::Iterator::operator << (Core* core) {
    set_core(core);
    return *this;
}

void SceneGraph::Iterator::find_next_node_depth() {
    if (!current_node_->get_children().empty()) {
        current_node_ = current_node_->get_children().front();
    } else {
        bool found_next(false);
        while (!found_next) {
            if (current_node_ != start_node_) {
                auto neighbour(get_neighbour(current_node_));
                if (neighbour) {
                    current_node_ = neighbour;
                    found_next = true;
                }
                else current_node_ = current_node_->get_parent();
            } else {
                *this = Iterator();
                break;
            }
        }
    }
}

void SceneGraph::Iterator::find_next_node_breadth() {
    int went_up(0);

    if (current_node_ == start_node_) {
        if (!current_node_->get_children().empty())
            current_node_ = current_node_->get_children().front();
        else *this = Iterator();
    } else {
        auto neighbour(get_neighbour(current_node_));
        while (!neighbour) {
            if (current_node_->get_parent() == start_node_)
                break;
            current_node_ = current_node_->get_parent();
            neighbour = get_neighbour(current_node_);
            ++went_up;
        }

        current_node_ = neighbour;

        while (went_up > 0) {
            current_node_ = current_node_->get_children().front();
            --went_up;
        }
    }
}

gua::SceneGraph::Node* SceneGraph::Iterator::get_neighbour(Node* to_be_checked) {
    auto end(to_be_checked->get_parent()->get_children().end());
    for (auto child(to_be_checked->get_parent()->get_children().begin()); child != end; ++child) {
        if (*child == to_be_checked) {
            if (++child != end) {
                return *child;
            } else break;
        }
    }

    return NULL;
}

}
