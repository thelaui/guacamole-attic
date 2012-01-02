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
/// \brief Declaration and definition of the GeometryNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_NODE_HPP
#define GEOMETRY_NODE_HPP

#include <eigen2/Eigen/Geometry>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a geometry for rendering.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

struct GeometryNode {
    GeometryNode(std::string const& g, std::string const& m, Eigen::Matrix4f const& t = Eigen::Matrix4f::Identity()):
        geometry_(g), material_(m), transform_(t) {}

    std::string geometry_;
    std::string material_;

    Eigen::Matrix4f transform_;
};

}

#endif //GEOMETRY_NODE_HPP

