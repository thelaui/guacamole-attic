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
/// \brief Declaration and definition of the GeometryNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_GEOMETRY_NODE_HPP
#define GUA_GEOMETRY_NODE_HPP

// external headers
#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a geometry for rendering.
///
/// This is a struct used for serializing the graph.
////////////////////////////////////////////////////////////////////////////////
struct GeometryNode {

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Constructor.
    ///
    /// This creates a new serialized node.
    ///
    /// \param geometry         The geometry of this node.
    /// \param material         The material of this geometry.
    /// \param transform        The global transformation of this node.
    ////////////////////////////////////////////////////////////////////////////
    GeometryNode(std::string const& geometry, std::string const& material,
                 math::mat4 const& transform):
        geometry_(geometry),
        material_(material),
        transform_(transform) {}

    ////////////////////////////////////////////////////////////////////////////
    ///\brief The geometry of this node.
    ////////////////////////////////////////////////////////////////////////////
    std::string geometry_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief The material of this geometry.
    ////////////////////////////////////////////////////////////////////////////
    std::string material_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief The global transformation of this node.
    ////////////////////////////////////////////////////////////////////////////
    math::mat4 transform_;
};

}

#endif // GUA_GEOMETRY_NODE_HPP

