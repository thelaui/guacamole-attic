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
/// \brief A Core representing geometry in a SceneGraph.
////////////////////////////////////////////////////////////////////////////////

#include "scenegraph/GeometryCore.hpp"

namespace gua {

GeometryCore::GeometryCore(std::string const& geometry, std::string const& material):
    Core(Core::GEOMETRY),
    geometry_(geometry),
    material_(material) {}

GeometryCore::~GeometryCore() {}

std::string const& GeometryCore::get_geometry() const {
    return geometry_;
}

std::string const& GeometryCore::get_material() const {
    return material_;
}

}
