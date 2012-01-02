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
/// \brief Declaration of the GeometryCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_CORE_HPP
#define GEOMETRY_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to represent geometry in the SceneGraph.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class GeometryCore: public Core {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a GeometryCore with the given parameters and calls
        /// the constructor of base class Core with the type GEOMETRY.
        ///
        ///\param geometry  The name of the GeometryCore's geometry.
        ///\param material  The name of the GeometryCoreCore's material.
        ////////////////////////////////////////////////////////////////////////
        GeometryCore(std::string const& geometry, std::string const& material);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a GeometryCore.
        ////////////////////////////////////////////////////////////////////////
        virtual ~GeometryCore();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the GeometryCore's name of geometry.
        ///
        ///\return geometry The geometry's name
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_geometry() const;

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the GeometryCore's name of material.
        ///
        ///\return material The material's name
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_material() const;

    private:
        std::string geometry_, material_;

};

}

#endif // GEOMETRY_CORE_HPP
