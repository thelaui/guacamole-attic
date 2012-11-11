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
/// \brief Declaration and definition of the CameraNode struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_CAMERA_NODE_HPP
#define GUA_CAMERA_NODE_HPP

// guacamole headers
#include "cores/CameraCore.hpp"

// external headers
#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a camera for rendering.
///
/// This is a struct used for serializing the graph.
////////////////////////////////////////////////////////////////////////////////
struct CameraNode {

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Constructor.
    ///
    /// This creates a new serialized node.
    ///
    /// \param core             The serialized core.
    /// \param transform        The global transformation of this node.
    ////////////////////////////////////////////////////////////////////////////
    CameraNode(CameraCore const& core, math::mat4 const& transform):
        transform_(transform),
        stereo_width_(core.get_stereo_width()) {}

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The global transformation of this node.
    ////////////////////////////////////////////////////////////////////////////
    math::mat4 transform_;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The eyeseparation.
    ////////////////////////////////////////////////////////////////////////////
    float stereo_width_;
};

}

#endif // GUA_CAMERA_NODE_HPP

