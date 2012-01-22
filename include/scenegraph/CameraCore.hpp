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
/// \brief Declaration of the CameraCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_CORE_HPP
#define CAMERA_CORE_HPP

#include "scenegraph/Core.hpp"

#include <eigen2/Eigen/Geometry>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to represent a camera in the SceneGraph.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class CameraCore: public Core {
    public:

        enum Type { MONO, SIDE_BY_SIDE, ANAGLYPH_RED_GREEN, ANAGLYPH_RED_CYAN };

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a CameraCore with the given parameters and calls
        /// the constructor of base class Core with the type CAMERA.
        ///
        ///\param fovy          The vertical opening angle of the frustum.
        ///\param aspect_ratio  The frustum's aspect ratio.
        ///\param near_plane    The frustum's near_plane.
        ///\param far_plane     The frustum's far_plane.
        ///\param stereo_width  The gap between the eyes.
        ///\param type          The type of the camera.
        ////////////////////////////////////////////////////////////////////////
        CameraCore(float fovy, float aspect_ratio, float near_plane, float far_plane,
                   float stereo_width = 0.f, Type type = MONO);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a CameraCore.
        ////////////////////////////////////////////////////////////////////////
        virtual ~CameraCore();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the CameraCore's viewing frustum.
        ///
        ///\return frustum The camera's frustum
        ////////////////////////////////////////////////////////////////////////
        Eigen::Matrix4f const& get_frustum() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the StereoCameraCore's gap between the eyes.
        ///
        ///\return The camera's eye gap.
        ////////////////////////////////////////////////////////////////////////
        float get_stereo_width() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the StereoCameraCore's type.
        ///
        ///\return The camera's type.
        ////////////////////////////////////////////////////////////////////////
        Type get_type() const;

    private:
        Eigen::Matrix4f frustum_;
        float stereo_width_;
        Type type_;
};

}

#endif // CAMERA_CORE_HPP
