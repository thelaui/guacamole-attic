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


#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a geometry for rendering.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

struct GeometryNode {
    GeometryNode(std::string const& g, std::string const& m, math::mat4 const& t = math::mat4::identity()):
        geometry_(g), material_(m), transform_(t) {}

    std::string geometry_;
    std::string material_;

    math::mat4 transform_;
};

}

#endif //GEOMETRY_NODE_HPP

