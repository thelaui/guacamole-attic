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
/// \brief Implementation of the math utilities.
////////////////////////////////////////////////////////////////////////////////

#include "utils/math.hpp"

#include <eigen2/Eigen/LU>

#include <iostream>

namespace gua {

Eigen::Matrix4f const math::compute_frustum(Eigen::Vector3f const& eye_position, Eigen::Matrix4f const& screen_transform,
                                            float near_plane, float far_plane) {

    Eigen::Vector4f relative_eye_position(screen_transform.inverse() * Eigen::Vector4f(eye_position[0], eye_position[1], eye_position[2], 1.0));

    float d(relative_eye_position.coeff(2));
    float ox(-relative_eye_position.coeff(0));
    float oy(-relative_eye_position.coeff(1));

    Eigen::Matrix4f frustum(Eigen::Matrix4f::Identity());

    frustum[0] = 2*d;
    frustum[5] = 2*d;
    frustum[8] = 2*ox ;
    frustum[9] = 2*oy ;
    frustum[10] = (-near_plane - far_plane) / (far_plane - near_plane);
    frustum[11] = -1.f;
    frustum[14] = -2*near_plane*far_plane / (far_plane - near_plane);
    frustum[15] = 0.f;

    return frustum;
}

}
