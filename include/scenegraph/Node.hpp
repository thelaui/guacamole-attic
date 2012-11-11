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
/// \brief Declaration of the Node class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_NODE_HPP
#define GUA_NODE_HPP

// guacamole headers
#include "scenegraph/SceneGraph.hpp"

// external headers
#include <set>
#include <list>
#include <vector>
#include <memory>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to build the internal structure of a SceneGraph.
///
/// Nodes have a name and hold objects and there transforms. Furthermore they
/// keep track of which Nodes are attached to them (children) an to which Node
/// they are attached to (parent). Nodes can be assigned a group name which
/// allows to group them concerning similar properties etc.
///
/// NOTE: This class is ment to be used inside the SceneGraph class only!
///       All interaction with the graph must be handled with Iterators and via
///       the SceneGraph interface.
///
////////////////////////////////////////////////////////////////////////////////

class SceneGraph::Node {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a Node with the given parameters.
        ///
        /// \param name      The Node's name
        /// \param transform The transformation of the object the Node contains.
        /// \param core      The Core of the node, representing its containing
        ///                 object.
        ////////////////////////////////////////////////////////////////////////
        Node(std::string const& name, math::mat4 transform = math::mat4::identity(),
             Core* core = NULL);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This destructs a Node and all its children.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Node();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a child.
        ///
        /// This adds a Node to the Node's children list.
        ///
        /// \param child     The Node to be added as a child.
        ////////////////////////////////////////////////////////////////////////
        void add_child(Node* child);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Removes a child.
        ///
        /// This removes a Node from the Node's children list.
        ///
        /// \param child     The Node to be removed.
        ////////////////////////////////////////////////////////////////////////
        void remove_child(Node* child);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's parent.
        ///
        /// \return Node     The Node's parent.
        ////////////////////////////////////////////////////////////////////////
        Node* get_parent() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the Node's parent.
        ///
        /// \param parent    The new parent of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_parent(Node* parent);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's children list.
        ///
        /// \return list     The Node's children list.
        ////////////////////////////////////////////////////////////////////////
        std::list<Node*> const& get_children() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's name.
        ///
        /// \return string   The Node's name.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_name() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the Node's name.
        ///
        /// \param name      The new name of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_name(std::string const& name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds the Node to a group.
        ///
        /// \param group     The name of the group the Node will be added to.
        ////////////////////////////////////////////////////////////////////////
        void add_to_group(std::string const& group);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds the Node to several groups.
        ///
        /// \param groups    The names of the groups the Node will be added to.
        ////////////////////////////////////////////////////////////////////////
        void add_to_groups(std::set<std::string> const& groups);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Removes the Node from a group.
        ///
        /// \param group     The name of the group the Node will removed from.
        ////////////////////////////////////////////////////////////////////////
        void remove_from_group(std::string const& group);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Checks whether the Node is in a certain group.
        ///
        /// \param group        The name of the group to be checked.
        ///
        /// \return is_in_group Returns true if the Node is in the given group,
        ///                     else false.
        ////////////////////////////////////////////////////////////////////////
        bool is_in_group(std::string const& group) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the groups the Node is in.
        ///
        /// \return groups   Returns all groups the Node is in.
        ////////////////////////////////////////////////////////////////////////
        std::set<std::string> const& get_groups() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the transformation of the object the Node contains.
        ///
        /// Returns the transformation accumulated with its parents so the
        /// resulting matrix represents the transformation in world
        /// coordinates.
        ///
        /// \return transform The Object's transformation.
        ////////////////////////////////////////////////////////////////////////
        math::mat4 const& get_transform() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the transformation of the object the Node contains.
        ///
        /// \param transform The new transformation of the Node's object.
        ////////////////////////////////////////////////////////////////////////
        void set_transform(math::mat4 const& transform);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's Core.
        ///
        /// Nodes carry pointers on objects of the base class Core. This base
        /// class can be obtained with this method.
        ///
        /// \return Core     The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        Core* get_core() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's Core, casted to it's type.
        ///
        /// Nodes carry base class pointers on Cores. Therefore a dynamic_cast
        /// is necessary. The resulting type of the returned core may be given
        /// as template parameter.
        ///
        /// \return Core     The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        T* get_core_casted() const {
            return dynamic_cast<T*>(core_);
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the Node's Core.
        ///
        /// \param core The new Core of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_core(Core* core);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a scaling on the Node's object's transformation.
        ///
        /// \param x         The x value of the scaling.
        /// \param y         The y value of the scaling.
        /// \param z         The z value of the scaling.
        ////////////////////////////////////////////////////////////////////////
        void scale(float x, float y, float z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a rotation on the Node's object's transformation.
        ///
        /// \param angle     The angle of the rotation in degrees.
        /// \param x         The x factor of the rotation.
        /// \param y         The y factor of the rotation.
        /// \param z         The z factor of the rotation.
        ////////////////////////////////////////////////////////////////////////
        void rotate(float angle, float x, float y, float z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a translation on the Node's object's transformation.
        ///
        /// \param x         The x value of the translation.
        /// \param y         The y value of the translation.
        /// \param z         The z value of the translation.
        ////////////////////////////////////////////////////////////////////////
        void translate(float x, float y, float z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the Node's depth.
        ///
        /// This function recursively computes the level the Node is on. Root
        /// Node has a depth of 0.
        ///
        /// \return depth     The Node's depth.
        ////////////////////////////////////////////////////////////////////////
        int get_depth() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the full path to the node.
        ///
        /// This function recursively computes the full path of the Node.
        ///
        /// \return path     The full path to the Node.
        ////////////////////////////////////////////////////////////////////////
        std::string const get_path() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Deep copies a Node with all its children.
        ///
        /// This function recursively generates new Nodes for the Node itself
        /// and all of its children.
        ///
        /// \return node     A pointer of the recently generated Node.
        ////////////////////////////////////////////////////////////////////////
        SceneGraph::Node* deep_copy() const;

    private:
        std::string name_;

        Node* parent_;
        std::list<Node*> children_;

        std::set<std::string> group_list_;

        math::mat4 transform_;

        Core* core_;
};

}

#endif // GUA_NODE_HPP
