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
/// \brief Declaration of a math utilities.
////////////////////////////////////////////////////////////////////////////////


#include <scm/core/math.h>
#include <scm/gl_core/math.h>

namespace gua {
    namespace math {

        typedef scm::math::mat<float, 4, 4> mat4;
        typedef scm::math::mat<float, 3, 3> mat3;

        typedef scm::math::vec<float, 4> vec4;
        typedef scm::math::vec<float, 3> vec3;
        typedef scm::math::vec<float, 2> vec2;

        math::mat4 const compute_frustum(math::vec4 const& eye_position, math::mat4 const& screen_transform,
                                         float near_plane, float far_plane);
    }
}

