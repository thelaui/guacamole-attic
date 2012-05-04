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
////////////////////////////////////////////////////////////////////////////////
struct LightNode {

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    LightNode(math::mat4 const& transform = math::mat4::identity(),
              Color3f const& color = Color3f()):
        transform_(transform),
        color_(color) {}

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    math::mat4 transform_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    Color3f color_;
};

}

#endif // GUA_LIGHT_NODE_HPP

