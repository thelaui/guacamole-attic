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
/// \brief A database for accessing material data.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/MaterialBase.hpp"

#include "include/renderer/Material.hpp"

MaterialBase() {}

MaterialBase::~MaterialBase() {}

void MaterialBase::add_material( std::string const& id, Material* material ) {}

bool MaterialBase::is_supported( std::string const& id ) const {}

Material* MaterialBase::get_material( std::string const& id ) const {}


