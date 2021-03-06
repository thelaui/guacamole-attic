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
/// \brief A Core representing light in a SceneGraph.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "cores/LightCore.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

LightCore::
LightCore(Color3f const& color):
    Core(Core::LIGHT),
    color_(color) {}

////////////////////////////////////////////////////////////////////////////////

LightCore::
~LightCore() {}

////////////////////////////////////////////////////////////////////////////////

Color3f const& LightCore::
get_color() const {

    return color_;
}

////////////////////////////////////////////////////////////////////////////////

}
