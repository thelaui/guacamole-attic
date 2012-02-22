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

#include "cores/CameraCore.hpp"

namespace gua {

CameraCore::CameraCore(float stereo_width, Type type):
    Core(Core::CAMERA),
    stereo_width_(stereo_width),
    type_(type) {}

CameraCore::~CameraCore() {}

float CameraCore::get_stereo_width() const {
    return stereo_width_;
}

CameraCore::Type CameraCore::get_type() const {
    return type_;
}

}
