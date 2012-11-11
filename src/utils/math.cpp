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
/// \brief Implementation of the math utilities.
////////////////////////////////////////////////////////////////////////////////

// header
#include "utils/math.hpp"

// external headers
#include <iostream>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

math::mat4 const math::
compute_frustum(math::vec4 const& eye_position, 
                math::mat4 const& screen_transform,
                float near_plane, float far_plane) {

    math::vec4 relative_eye_position(scm::math::inverse(screen_transform) 
                                     * eye_position);

    float d(relative_eye_position[2]);
    float ox(-relative_eye_position[0]);
    float oy(-relative_eye_position[1]);

    math::mat4 frustum(math::mat4::identity());

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

////////////////////////////////////////////////////////////////////////////////

}
