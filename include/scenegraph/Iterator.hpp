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
/// \brief Declaration of the Iterator class.
////////////////////////////////////////////////////////////////////////////////

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "scenegraph/SceneGraph.hpp"
#include "scenegraph/Node.hpp"
#include "utils/debug.hpp"

#include <memory>
#include <map>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to iterate over the SceneGraph.
///
/// Iterators are used to give access to the SceneGraph's data without having
/// to worry about its inner structure. They are very useful to get access to
/// the nodes one by one in preorder traversion.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class SceneGraph::Iterator {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a Iterator from a given Node.
        ///
        ///\param node      The Node the Iterator shall contain.
        ///\param type           The type of the Iterator.
        ////////////////////////////////////////////////////////////////////////
        Iterator(Node* node = NULL, IterationType type = DEPTH_FIRST);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Adds a new Node.
        ///
        /// This function adds a new Node beyond the Node the Iterator holds.
        ///
        ///\param node_name      The name of the new Node.
        ///\param core           The core the new Node shall refer to.
        ///\param transform      The transformation of the object the new Node
        ///                      carries.
        ///
        ///\return Iterator      An Iterator on the recently added Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator add_node(std::string const& node_name, Core* core = NULL,
                          Eigen::Transform3f const& transform =
                          (Eigen::Transform3f) Eigen::Transform3f::Identity());

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the depth of the Iterator.
        ///
        /// This effectively returns the depth of the Node the Iterator is
        /// currently pointing on.
        ///
        ///\return depth      The depth of the Iterator.
        ////////////////////////////////////////////////////////////////////////
        int get_depth() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the name of the Iterator's Node.
        ///
        ///\return name       The depth of the Iterator' Node.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_name() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the name of the Iterator's Node.
        ///
        ///\param name        The new name of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_name(std::string const& name) const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the transformation of the Iterator's Node.
        ///
        /// Returns the accumulation of the local and global transformation.
        ///
        ///\return transform  The Node's transformation.
        ////////////////////////////////////////////////////////////////////////
        Eigen::Transform3f const& get_transform(InheritanceMode mode = PUBLIC) const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the transformation of the Iterator's Node.
        ///
        ///\param transform   The new transformation of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_transform(Eigen::Transform3f const& transform, InheritanceMode mode = PUBLIC) const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the core of the Iterator's Node.
        ///
        /// Returns the base of the contained Core.
        ///
        ///\return Core  The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        Core* get_core() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns a casted core of the Iterator's Node.
        ///
        /// The Core's type may be given as template parameter. A dynamic_cast
        /// will be applied in the function Node::get_core().
        ///
        ///\return Core  The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        template <class T>
        T* get_core_casted() const {
            if (current_node_) {
                auto casted_core(current_node_->get_core_casted<T>());
                if (!casted_core)
                    WARNING("The core you are trying to get is not of the type you expect!");
                return casted_core;
            }
            return NULL;
        }

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the core of the Iterator's Node.
        ///
        ///\param core   The new core of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_core(Core* core) const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a scaling on the Iterator's Node's transformation.
        ///
        ///\param x         The x value of the scaling.
        ///\param y         The y value of the scaling.
        ///\param z         The z value of the scaling.
        ///\param transform_mode   Whether the transformation is applied in
        ///                        object or world coordinates.
        ///\param inheritance_mode Whether the transformation should affect
        ///                        children of this node.
        ////////////////////////////////////////////////////////////////////////
        void scale(double x, double y, double z,
                   TransformMode transform_mode = GLOBAL,
                   InheritanceMode inheritance_mode = PUBLIC);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a rotation on the Iterator's Node's transformation.
        ///
        ///\param angle     The angle of the rotation in radians.
        ///\param x         The x factor of the rotation.
        ///\param y         The y factor of the rotation.
        ///\param z         The z factor of the rotation.
        ///\param transform_mode   Whether the transformation is applied in
        ///                        object or world coordinates.
        ///\param inheritance_mode Whether the transformation should affect
        ///                        children of this node.
        ////////////////////////////////////////////////////////////////////////
        void rotate(double angle, double x, double y, double z,
                    TransformMode transform_mode = GLOBAL,
                    InheritanceMode inheritance_mode = PUBLIC);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Applies a translation on the Iterator's Node's transformation.
        ///
        ///\param x         The x value of the translation.
        ///\param y         The y value of the translation.
        ///\param z         The z value of the translation.
        ///\param transform_mode   Whether the transformation is applied in
        ///                        object or world coordinates.
        ///\param inheritance_mode Whether the transformation should affect
        ///                        children of this node.
        ////////////////////////////////////////////////////////////////////////
        void translate(double x, double y, double z,
                       TransformMode transform_mode = GLOBAL,
                       InheritanceMode inheritance_mode = PUBLIC);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the Iterator's type.
        ///
        /// This can be used to change the way the Iterator is incremented.
        ////////////////////////////////////////////////////////////////////////
        void set_iteration_type(IterationType type);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Increments the Iterator.
        ///
        /// Increments the Iterator by detecting the next node of the SceneGraph
        /// in preorder traversion and setting the Iterator's node to this one.
        /// If every node is visited, the Iterator will be set on "end".
        ////////////////////////////////////////////////////////////////////////
        void operator ++();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Compares two Iterators.
        ///
        /// This function returns true if two Iterators point on the same Node.
        ///
        ///\param rhs       The Iterator to be checked on equality with.
        ///
        ///\return result   The result of the comparison.
        ////////////////////////////////////////////////////////////////////////
        bool operator ==(Iterator const& rhs);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Compares two Iterators.
        ///
        /// This function returns true if two Iterators do not point on the same
        /// Node.
        ///
        ///\param rhs       The Iterator to be checked on equality with.
        ///
        ///\return result   The result of the comparison.
        ////////////////////////////////////////////////////////////////////////
        bool operator !=(Iterator const& rhs);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the name of the Iterator's Node.
        ///
        ///\param name        The new name of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (std::string const& name);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the transformation of the Iterator's Node
        ///
        ///\param transform   The new transformation of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (Eigen::Transform3f const& transform);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Sets the core of the Iterator's Node.
        ///
        ///\param core        The new core of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (Core*core);

    private:
        Node* current_node_;
        Node* start_node_;

        SceneGraph::IterationType type_;

        std::map<int, std::list<Node*>> breadth_nodes_;
        unsigned current_depth_;

        void find_next_node_depth();
        void find_next_node_breadth();

        Node* get_neighbour(Node* to_be_checked);

        static const std::string end_name_;
        static const Eigen::Transform3f end_transform_;
};

}

#endif //ITERATOR_HPP
