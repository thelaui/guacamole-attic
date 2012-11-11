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
/// \brief Declaration and definition of the LightNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_LIGHT_NODE_HPP
#define GUA_LIGHT_NODE_HPP

// guacamole headers
#include "utils/Color3f.hpp"
#include "utils/math.hpp"

// external headers
#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a light for rendering.
///
/// This is a struct used for serializing the graph.
////////////////////////////////////////////////////////////////////////////////
struct LightNode {

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Constructor.
    ///
    /// This creates a new serialized node.
    ///
    /// \param transform        The global transformation of this node.
    /// \param color            The color of the light.
    ////////////////////////////////////////////////////////////////////////////
    LightNode(math::mat4 const& transform, Color3f const& color):
        transform_(transform),
        color_(color) {}

    ////////////////////////////////////////////////////////////////////////////
    ///\brief The global transformation of this node.
    ////////////////////////////////////////////////////////////////////////////
    math::mat4 transform_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief The color of the light.
    ////////////////////////////////////////////////////////////////////////////
    Color3f color_;
};

}

#endif // GUA_LIGHT_NODE_HPP

