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

Eigen::Matrix4f const math::compute_frustum(Eigen::Matrix4f const& eye_transform, Eigen::Matrix4f const& screen_transform,
                                            float near_plane, float far_plane) {

    Eigen::Transform3f relative_eye(screen_transform.inverse() * eye_transform);
    Eigen::Transform3f::TranslationPart eye_position(relative_eye.translation());

    float d(eye_position.coeff(2));
    float ox(-eye_position.coeff(0));
    float oy(-eye_position.coeff(1));

    Eigen::Vector4f bottom_left(screen_transform * Eigen::Vector4f(-0.5, -0.5, 0, 1));
    Eigen::Vector4f up_left(screen_transform * Eigen::Vector4f(-0.5, 0.5, 0, 1));
    Eigen::Vector4f up_right(screen_transform * Eigen::Vector4f(0.5, 0.5, 0, 1));

    Eigen::Vector4f width_vector(up_left - up_right);
    Eigen::Vector4f height_vector(up_left - bottom_left);

    float width(std::sqrt(std::pow(width_vector[0], 2)
                         +std::pow(width_vector[1], 2)
                         +std::pow(width_vector[2], 2)));

    float height(std::sqrt(std::pow(height_vector[0], 2)
                          +std::pow(height_vector[1], 2)
                          +std::pow(height_vector[2], 2)));

    Eigen::Matrix4f frustum(Eigen::Matrix4f::Identity());

    frustum[0] = 2*d / width;
    frustum[5] = 2*d / height;
    frustum[8] = 2*ox / width;
    frustum[9] = 2*oy / height;
    frustum[10] = (- far_plane - near_plane) / (far_plane - near_plane);
    frustum[11] = -1.f;
    frustum[14] = -2*near_plane*far_plane / (far_plane - near_plane);

    return frustum;
}

}
