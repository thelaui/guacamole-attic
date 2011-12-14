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
/// \brief Declaration and definition of the CameraNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_NODE_HPP
#define CAMERA_NODE_HPP

#include <eigen2/Eigen/Geometry>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a camera for rendering.
///
////////////////////////////////////////////////////////////////////////////////

struct CameraNode {
    CameraNode() {};
    CameraNode(Eigen::Matrix4f const& projection, Eigen::Matrix4f const& t = Eigen::Matrix4f::Identity()):
        projection_(projection), transform_(t) {}

    Eigen::Matrix4f projection_;
    Eigen::Matrix4f transform_;
};

#endif //CAMERA_NODE_HPP

