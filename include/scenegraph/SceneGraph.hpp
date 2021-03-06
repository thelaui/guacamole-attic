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
/// \brief Declaration of the SceneGraph class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_SCENE_GRAPH_HPP
#define GUA_SCENE_GRAPH_HPP

#include "scenegraph/Core.hpp"
#include "utils/math.hpp"

#include <string>
#include <list>

namespace gua {

class GeometryCore;
class LightCore;
class CameraCore;

////////////////////////////////////////////////////////////////////////////////
/// \brief A class to represent a scene.
///
/// This class is used to build and structure a graph describing a scene with
/// all its contents. It provides an interface to set up and have access to
/// a graph consisting of several Nodes in order to build a scene abstraction.
////////////////////////////////////////////////////////////////////////////////
class SceneGraph {

    public: class Iterator;
    private: class Node;

    public:

        ////////////////////////////////////////////////////////////////////////
        /// This enumeration is used to distinguish between different traversion
        /// styles.
        ////////////////////////////////////////////////////////////////////////
        enum IterationType {DEPTH_FIRST, BREADTH_FIRST};

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs an empty SceneGraph.
        ////////////////////////////////////////////////////////////////////////
        SceneGraph();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Copy Constructor.
        ///
        /// This constructs a copy of a given SceneGraph.
        ///
        /// \param graph    The SceneGraph to be copied.
        ////////////////////////////////////////////////////////////////////////
        SceneGraph(SceneGraph const& graph);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This destructs the SceneGraph with all its contents.
        ////////////////////////////////////////////////////////////////////////
        virtual ~SceneGraph();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new Node.
        ///
        /// This function adds a new Node to the graph. If the given path to a
        /// parent Node is invalid (this means this Node doesn't exist), an
        /// Iterator on the SceneGraph's "end" is returned. Otherwise an
        /// Iterator on the added Node is given back.
        ///
        /// \param path_to_parent The location of the Node the new Node will be
        ///                       attached to.
        /// \param node_name      The name of the new Node.
        /// \param core           The core the new Node shall refer to.
        /// \param transform      The transformation of the object the new Node
        ///                       carries.
        ///
        /// \return Iterator      An Iterator on the recently added Node. If the
        ///                       path to the parent was invalid, the returned
        ///                       Iterator points to the SceneGraph's "end".
        ////////////////////////////////////////////////////////////////////////
        Iterator add_node(std::string const& path_to_parent,
                          std::string const& node_name, Core* core = NULL,
                          math::mat4 const& transform = math::mat4::identity());

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new Node.
        ///
        /// This function adds a new Node to the graph. If the given path to a
        /// parent Node is invalid (this means this Node doesn't exist), an
        /// Iterator on the SceneGraph's "end" is returned. Otherwise an
        /// Iterator on the added Node is given back.
        ///
        /// \param parent         An Iterator to the Node the new Node will be
        ///                       attached to.
        /// \param node_name      The name of the new Node.
        /// \param core           The core the new Node shall refer to.
        /// \param transform      The transformation of the object the new Node
        ///                       carries.
        ///
        /// \return Iterator      An Iterator on the recently added Node. If the
        ///                       path to the parent was invalid, the returned
        ///                       Iterator points to the SceneGraph's "end".
        ////////////////////////////////////////////////////////////////////////
        Iterator add_node(Iterator const& parent,
                          std::string const& node_name, Core* core = NULL,
                          math::mat4 const& transform = math::mat4::identity());

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new Node.
        ///
        /// This function adds a new Node to the graph. If the given path to a
        /// parent Node is invalid (this means this Node doesn't exist), all
        /// missing nodes are constructed with default values and added to the
        /// graph.
        ///
        /// \param path_to_parent The location of the Node the new Node will be
        ///                       attached to.
        /// \param node_name      The name of the new Node.
        /// \param core           The core the new Node shall refer to.
        /// \param transform      The transformation of the object the new Node
        ///                       carries.
        ///
        /// \return Iterator      An Iterator on the recently added Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator add_node_recursively(std::string const& path_to_parent,
                                      std::string const& node_name,
                                      Core* core = NULL,
                                      math::mat4 const& transform =
                                                        math::mat4::identity());

        ////////////////////////////////////////////////////////////////////////
        /// \brief Removes a Node.
        ///
        /// This function removes a Node from the graph and returnes an Iterator
        /// on the next Node with respect to the Iterator's traversion style.
        ///
        /// \param path_to_node   The location of the Node to be removed.
        ///
        /// \return Iterator      An Iterator on the next Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator remove_node(std::string const& path_to_node);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Moves a Node.
        ///
        /// This function moves a Node and all its children from one position in
        /// the graph to another one.
        ///
        /// NOTE: If path_to_node ends with a '/', the moved Node will be
        ///       attached to the target. If it doesn't end with '/', the target
        ///       will be overwritten.
        ///
        /// \param path_to_node   The location of the Node to be moved.
        /// \param path_to_target The location of the target the Node will be
        ///                       moved to.
        ///
        /// \return Iterator      An Iterator on the moved Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator move_node(std::string const& path_to_node,
                           std::string const& path_to_target);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Copies a Node.
        ///
        /// This function copies a Node and all its children from one position
        /// in the graph to another one.
        ///
        /// NOTE: If path_to_node ends with a '/', the copied Node will be
        ///       attached to the target. If it doesn't end with '/', the target
        ///       will be overwritten.
        ///
        ///\param path_to_node   The location of the Node to be copied.
        ///\param path_to_target The location of the target the Node will be
        ///                      copied to.
        ///
        ///\return Iterator      An Iterator on the copied Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator copy_node(std::string const& path_to_node,
                           std::string const& path_to_target);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the working Node.
        ///
        /// This function sets the Node you are currently working at. This
        /// allows to operate on nodes from within a subtree and therefore
        /// paths to nodes can be much shorter.
        ///
        /// \param path_to_node   The location of the Node to be set as the
        ///                       working Node.
        ///
        ////////////////////////////////////////////////////////////////////////
        void set_working_node(std::string const& path_to_node);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns an iterator to a Node.
        ///
        /// This function returns an iterator to a Node which may be used to
        /// apply operations.
        ///
        /// \param path_to_node   The location of the Node to be encapsulated in
        ///                       the Iterator.
        /// \param type           The traversion type of the Iterator.
        ///
        /// \return Iterator      An Iterator on the given Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator get_iterator(std::string const& path_to_node,
                              IterationType type = DEPTH_FIRST) const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns an iterator to the beginning of the SceneGraph.
        ///
        /// This function returns an iterator to the beginning of the
        /// SceneGraph which is a Node named "/".
        ///
        ///\param type           The traversion type of the Iterator.
        ///
        ///\return Iterator      An Iterator on the Node "/".
        ////////////////////////////////////////////////////////////////////////
        Iterator begin(IterationType type = DEPTH_FIRST) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns an iterator to the "end" of the SceneGraph.
        ///
        /// Because the SceneGraph is structured as a non-cyclic graph is
        /// expected to be, there is no real "end". Therefore this function
        /// returns an Iterator on an imaginary end, which can be used to
        /// check whether an added Node is valid or an iteration over the graph
        /// has finished.
        ///
        /// \return Iterator      An Iterator on the "end" of the SceneGraph.
        ////////////////////////////////////////////////////////////////////////
        Iterator end() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Locks the SceneGraph.
        ///
        /// This function locks the SceneGraph in order to have save accesses
        /// in multi-threaded applications.
        ////////////////////////////////////////////////////////////////////////
        void lock();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Unlocks the SceneGraph.
        ///
        /// This function unlocks the SceneGraph in order to have save accesses
        /// in multi-threaded applications.
        ////////////////////////////////////////////////////////////////////////
        void unlock();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Allows to access nodes via the index operator.
        ///
        /// This operator allows to access nodes via the index operator. If a
        /// given path doesn't refer to an existing set of nodes, all missing
        /// nodes in the path are added to the SceneGraph.
        ///
        ///\param path_to_node   The path to the Node you want to access.
        ///
        ///\return Iterator      An Iterator on the given Node.
        ////////////////////////////////////////////////////////////////////////
        Iterator operator [](std::string const& path_to_node);
        SceneGraph const& operator= (SceneGraph const& rhs);

    private:
        Node *root_, *working_node_;

        Node* find_node(std::string const& path_to_node,
                        std::string const& path_to_start = "/",
                        bool add_missing_nodes = false) const;

        bool has_child(Node* parent, std::string const& child_name) const;
};

////////////////////////////////////////////////////////////////////////////////
///\brief The stream operator.
///
/// This operator allows to stream the names of the SceneGraph's nodes into a
/// given ostream.
///
///\param os         The ostream the names will be streamed into.
///\param graph      The SceneGraph to be streamed.
///
///\return ostream   A reference to the manipulated stream given to the
///                  function.
////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, SceneGraph const& graph);

}

#endif // GUA_SCENE_GRAPH_HPP
