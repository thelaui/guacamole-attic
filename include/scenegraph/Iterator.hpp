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
/// \brief Declaration of the Iterator class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_ITERATOR_HPP
#define GUA_ITERATOR_HPP

// guacamole headers
#include "scenegraph/SceneGraph.hpp"
#include "scenegraph/Node.hpp"
#include "utils/debug.hpp"

// external headers
#include <memory>
#include <map>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to iterate over the SceneGraph.
///
/// Iterators are used to give access to the SceneGraph's data without having
/// to worry about its inner structure. They are very useful to get access to
/// the nodes one by one in breadth or depth first style traversion.
///
////////////////////////////////////////////////////////////////////////////////
class SceneGraph::Iterator {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs an Iterator on a given Node.
        ///
        /// \param node      The Node the Iterator shall contain.
        /// \param type      The type of the Iterator. Can be DEPTH_FIRST or
        ///                  BREADTH_FIRST
        ////////////////////////////////////////////////////////////////////////
        Iterator(Node* node = NULL, IterationType type = DEPTH_FIRST);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new Node.
        ///
        /// This function adds a new Node to the children list of the Node
        /// the Iterator holds.
        ///
        /// \param node_name      The name of the new Node.
        /// \param core           The core the new Node shall refer to.
        /// \param transform      The transformation of the object the new Node
        ///                      carries.
        ///
        /// \return Iterator      An Iterator on the recently added Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator add_child(std::string const& node_name, Core* core = NULL,
                           math::mat4 const& transform =
                           math::mat4::identity()) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the depth of the Iterator.
        ///
        /// This returns the depth of the Node the Iterator is currently
        /// referring to.
        ///
        /// \return depth      The depth of the Iterator.
        ////////////////////////////////////////////////////////////////////////
        int get_depth() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the name of the Iterator's Node.
        ///
        /// \return name       The depth of the Iterator' Node.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_name() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the name of the Iterator's Node.
        ///
        /// \param name        The new name of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_name(std::string const& name) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds the Iterator's Node to a group.
        ///
        /// \param group     The name of the group the Node will be added to.
        ////////////////////////////////////////////////////////////////////////
        void add_to_group(std::string const& group);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds the Iterator's Node to several groups.
        ///
        /// \param groups    The names of the groups the Node will be added to.
        ////////////////////////////////////////////////////////////////////////
        void add_to_groups(std::set<std::string> const& groups);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Removes the Iterator's Node from a group.
        ///
        /// \param group     The name of the group the Node will removed from.
        ////////////////////////////////////////////////////////////////////////
        void remove_from_group(std::string const& group);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Checks whether the Iterator's Node is in a certain group.
        ///
        /// \param group        The name of the group to be checked.
        ///
        /// \return is_in_group Returns true if the Node is in the given group,
        ///                     else false.
        ////////////////////////////////////////////////////////////////////////
        bool is_in_group(std::string const& group) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the groups the Iterator's Node is in.
        ///
        /// \return groups   Returns all groups the Node is in.
        ////////////////////////////////////////////////////////////////////////
        std::set<std::string> const& get_groups() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the transformation of the Iterator's Node.
        ///
        /// Returns the accumulation of the local and global transformation.
        ///
        /// \return transform  The Node's transformation.
        ////////////////////////////////////////////////////////////////////////
        math::mat4 const& get_transform() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the transformation of the Iterator's Node.
        ///
        /// \param transform   The new transformation of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_transform(math::mat4 const& transform) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the core of the Iterator's Node.
        ///
        /// Returns the base of the contained Core.
        ///
        /// \return Core  The Node's Core.
        ////////////////////////////////////////////////////////////////////////
        Core* get_core() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns a casted core of the Iterator's Node.
        ///
        /// The Core's type may be given as template parameter. A dynamic_cast
        /// will be applied in the function Node::get_core().
        ///
        /// \return Core  The Node's Core.
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
        /// \brief Sets the core of the Iterator's Node.
        ///
        /// \param core   The new core of the Node.
        ////////////////////////////////////////////////////////////////////////
        void set_core(Core* core) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a scaling on the Iterator's Node's transformation.
        ///
        /// \param x         The x value of the scaling.
        /// \param y         The y value of the scaling.
        /// \param z         The z value of the scaling.
        ////////////////////////////////////////////////////////////////////////
        void scale(double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a rotation on the Iterator's Node's transformation.
        ///
        /// \param angle     The angle of the rotation in degrees.
        /// \param x         The x factor of the rotation.
        /// \param y         The y factor of the rotation.
        /// \param z         The z factor of the rotation.
        ////////////////////////////////////////////////////////////////////////
        void rotate(double angle, double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies a translation on the Iterator's Node's
        ///        transformation.
        ///
        /// \param x         The x value of the translation.
        /// \param y         The y value of the translation.
        /// \param z         The z value of the translation.
        ////////////////////////////////////////////////////////////////////////
        void translate(double x, double y, double z);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the Iterator's type.
        ///
        /// This can be used to change the way the Iterator is incremented in
        /// order to change the traversion style.
        ///
        /// \param type      The new type of the Iterator.
        ////////////////////////////////////////////////////////////////////////
        void set_iteration_type(IterationType type);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Increments the Iterator.
        ///
        /// Increments the Iterator by detecting the next node of the SceneGraph
        /// with respect to the Iterator's type and setting the Iterator's node
        /// to this one. If every node is visited, the Iterator will be set on
        /// "end".
        ////////////////////////////////////////////////////////////////////////
        void operator ++();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Compares two Iterators.
        ///
        /// This function returns true if two Iterators point on the same Node.
        ///
        /// \param rhs       The Iterator to be checked on equality with.
        ///
        /// \return result   The result of the comparison.
        ////////////////////////////////////////////////////////////////////////
        bool operator ==(Iterator const& rhs);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Compares two Iterators.
        ///
        /// This function returns true if two Iterators do not point on the same
        /// Node.
        ///
        /// \param rhs       The Iterator to be checked on equality with.
        ///
        /// \return result   The result of the comparison.
        ////////////////////////////////////////////////////////////////////////
        bool operator !=(Iterator const& rhs);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the name of the Iterator's Node.
        ///
        /// \param name        The new name of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (std::string const& name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the transformation of the Iterator's Node
        ///
        /// \param transform   The new transformation of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (math::mat4 const& transform);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the core of the Iterator's Node.
        ///
        /// \param core        The new core of the Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator& operator << (Core*core);

    private:
        mutable Node* current_node_;
        Node* start_node_;

        SceneGraph::IterationType type_;

        std::map<int, std::list<Node*>> breadth_nodes_;
        unsigned current_depth_;

        void find_next_node_depth();
        void find_next_node_breadth();

        Node* get_neighbour(Node* to_be_checked);

        static const std::string end_name_;
        static const math::mat4 end_transform_;
};

}

#endif // GUA_ITERATOR_HPP
