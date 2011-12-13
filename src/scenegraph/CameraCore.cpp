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
/// \brief A Core representing a camera in a SceneGraph.
////////////////////////////////////////////////////////////////////////////////

#include "include/scenegraph/CameraCore.hpp"

CameraCore::CameraCore(float fovy, float aspect_ratio, float near_plane, float far_plane):
    Core(Core::CAMERA),
    frustum_(Eigen::Matrix4f::Identity()) {

    const float y_scale = std::tan(M_PI_2 - M_PI/180.f*(fovy / 2));
    const float x_scale = y_scale / aspect_ratio;
    const float frustum_length = far_plane - near_plane;

    frustum_[0] = x_scale;
    frustum_[5] = y_scale;
    frustum_[10] = -((far_plane + near_plane) / frustum_length);
    frustum_[11] = -1;
    frustum_[14] = -((2 * near_plane * far_plane) / frustum_length);
}

CameraCore::~CameraCore() {}

Eigen::Matrix4f const& CameraCore::get_frustum() const {
    return frustum_;
}

