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
/// \brief Declaration of the GeometryBase class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_BASE_HPP
#define GEOMETRY_BASE_HPP

#include "utils/Singleton.hpp"
#include "renderer/DataBase.hpp"
#include "renderer/Geometry.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief A data base for meshes.
///
/// This DataBase stores geometry data. It can be accessed via string
/// identifiers.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class GeometryBase: public DataBase<Geometry>, public Singleton<GeometryBase> {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Pre-loads some meshes.
        ///
        /// This method loads some default meshes to the data base. For example
        /// a simple cube ("cube"), the famous Utah Teapot ("teapot") and
        /// Suzanne from Blender ("monkey").
        ////////////////////////////////////////////////////////////////////////
        static void load_objects_from(std::string const& path_to_objects);

        friend class Singleton<GeometryBase>;

    private:
        GeometryBase() {};
        ~GeometryBase() {};
};

}

#endif // GEOMETRY_BASE_HPP


