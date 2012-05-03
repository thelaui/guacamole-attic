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

#ifndef GUA_CAMERA_CORE_HPP
#define GUA_CAMERA_CORE_HPP

#include "scenegraph/Core.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to represent a camera in the SceneGraph.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class CameraCore: public Core {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a CameraCore with the given parameters and calls
        /// the constructor of base class Core with the type CAMERA.
        ///
        ///\param stereo_width  The gap between the eyes.
        ////////////////////////////////////////////////////////////////////////
        CameraCore(float stereo_width = 0.f);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a CameraCore.
        ////////////////////////////////////////////////////////////////////////
        virtual ~CameraCore();


        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the StereoCameraCore's gap between the eyes.
        ///
        ///\return The camera's eye gap.
        ////////////////////////////////////////////////////////////////////////
        float get_stereo_width() const;

    private:
        float stereo_width_;
};

}

#endif // GUA_CAMERA_CORE_HPP
