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
/// \brief Declaration of the Node class.
////////////////////////////////////////////////////////////////////////////////

#ifndef Node_HPP
#define Node_HPP

#include <list>
#include <memory>
#include <eigen2/Eigen/Geometry>

#include "include/scenegraph/SceneGraph.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to build the internal structure of a SceneGraph.
///
/// Nodes have a name and hold objects and there transforms. Furthermore they
/// keep track of which Nodes are attached to them (children) an to which Node
/// they are attached to (parent).
///
/// NOTE: This class is ment to be used inside the SceneGraph class only!
///       All interaction with the graph must be handled with Iterators.
///
////////////////////////////////////////////////////////////////////////////////

class SceneGraph::Node {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a Node with the given parameters.
        ///
        ///\param name      The Node's name
        ///\param transform The transformation of the object the Node contains.
        ///\param core      The Core of the node, representing its containing
        ///                 object.
        ////////////////////////////////////////////////////////////////////////
        Node(std::string const& name, Eigen::Transform3f transform = (Eigen::Transform3f)Eigen::Matrix3f::Identity(),
             Core* core = NULL);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a Node and all its children.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Node();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Adds a child.
        ///
        /// This adds a Node to the Node's children.
        ///\param child     The Node to be added as a child.
        ////////////////////////////////////////////////////////////////////////
        void add_child(Node* child);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Removes a child.
        ///
        /// This removes a Node from the Node's children.
        ///\param child     The Node to be removed.
        ////////////////////////////////////////////////////////////////////////
        void remove_child(Node* child);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Node's parent.
        ///
        ///\return Node     The Node's parent.
        ////////////////////////////////////////////////////////////////////////
        Node* get_parent() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the Node's parent.
        ///
        ///\param parent    The new parent of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_parent(Node* parent);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Node's children.
        ///
        ///\return list     The Node's children.
        ////////////////////////////////////////////////////////////////////////
        std::list<Node*> const& get_children() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Node's name.
        ///
        ///\return string   The Node's name.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_name() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the Node's name.
        ///
        ///\param name      The new name of the node.
        ////////////////////////////////////////////////////////////////////////
        void set_name(std::string const& name);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the transformation of the object the Node contains.
        ///
        ///\return transform The Object's transformation.
        ////////////////////////////////////////////////////////////////////////
        Eigen::Transform3f const& get_transform() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the transformation of the object the Node contains.
        ///
        ///\param transform The new transformation of the Node's object.
        ////////////////////////////////////////////////////////////////////////
        void set_transform(Eigen::Transform3f const& transform);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Node's Core.
        ///
        /// Nodes carry base class pointers on Cores. Therefore a dynamic_cast
        /// is necessary. The resulting type of the returned core may be given
        /// as template parameter.
        ///
        ///\return Core     The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        template <class T = Core>
        T* get_core() const {
            return dynamic_cast<T*>(core_);
        }

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the Node's Core.
        ///
        ///\param core The new Core of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_core(Core* core);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a scaling on the Node's transformation.
        ///
        ///\param x         The x value of the scaling.
        ///\param y         The y value of the scaling.
        ///\param z         The z value of the scaling.
        ////////////////////////////////////////////////////////////////////////
        void scale(double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a rotation on the Node's transformation.
        ///
        ///\param angle     The angle of the rotation in radians.
        ///\param x         The x factor of the rotation.
        ///\param y         The y factor of the rotation.
        ///\param z         The z factor of the rotation.
        ////////////////////////////////////////////////////////////////////////
        void rotate(double angle, double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a translation on the Node's transformation.
        ///
        ///\param x         The x value of the translation.
        ///\param y         The y value of the translation.
        ///\param z         The z value of the translation.
        ////////////////////////////////////////////////////////////////////////
        void translate(double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Node's depth.
        ///
        /// This function recursively computes the level the Node is on. Root
        /// Node has a depth of 0.
        ///
        ///\return depth     The Node's depth.
        ////////////////////////////////////////////////////////////////////////
        int get_depth() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the full path to the node.
        ///
        /// This function recursively computes the full path of the Node.
        ///
        ///\return path     The full path to the Node.
        ////////////////////////////////////////////////////////////////////////
        std::string const get_path() const;

    private:
        std::string name_;

        Node* parent_;
        std::list<Node*> children_;

        Eigen::Transform3f transform_;
        Core* core_;
};


#endif //Node_HPP
