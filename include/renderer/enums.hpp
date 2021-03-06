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
/// \brief Some basic type definitions for guacamole.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_ENUMS_HPP
#define GUA_ENUMS_HPP

namespace gua {

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Eye of a camera.
    ///
    /// An enumeration used for determining from which point of view a scene
    /// has to be rendered. Either from the left eye of a camera, from the
    /// right or from the exact camera position.
    ////////////////////////////////////////////////////////////////////////////
    enum CameraMode { CENTER,
                      LEFT,
                      RIGHT };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Stereo mode for a pipeline.
    ///
    /// Determines how two stereo images should be mapped to each other.
    ////////////////////////////////////////////////////////////////////////////
    enum StereoMode { MONO,
                      SIDE_BY_SIDE,
                      ANAGLYPH_RED_GREEN,
                      ANAGLYPH_RED_CYAN };
}

#endif // GUA_ENUMS_HPP
