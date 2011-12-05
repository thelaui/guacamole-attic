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
/// \brief A database for accessing geometry data.
////////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_BASE_HPP
#define GEOMETRY_BASE_HPP

#include <string>
#include <map>

#include "include/utils/KnownObject.hpp"

class Mesh;

class GeometryBase: public KnownObject<GeometryBase> {
    public:
        GeometryBase();
        virtual ~GeometryBase();

        void add_geometry(std::string const& id, Mesh* geometry);
        bool is_supported(std::string const& id) const;

        Mesh* get_geometry(std::string const& id) const;

    private:
        std::map<std::string, Mesh*> geometries_;
};

#endif // GEOMETRY_BASE_HPP
