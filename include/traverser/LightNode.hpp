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
/// \brief Declaration and definition of the LightNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef LIGHT_NODE_HPP
#define LIGHT_NODE_HPP

#include "utils/Color3f.hpp"
#include "utils/math.hpp"

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a light for rendering.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

struct LightNode {
    LightNode(math::mat4 const& trans = math::mat4::identity(),
              Color3f const& clr = Color3f()):
        transform(trans),
        color(clr) {}

    math::mat4 transform;
    Color3f color;
};

}

#endif //LIGHT_NODE_HPP

