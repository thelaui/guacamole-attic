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
/// \brief Declaration of the LightCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef LIGHT_CORE_HPP
#define LIGHT_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to represent light in the SceneGraph.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class LightCore: public Core {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a LightCore with the given parameter and calls
        /// the constructor of base class Core with the type LIGHT.
        ///
        ///\param color  The name of the LightCore's color.
        ////////////////////////////////////////////////////////////////////////
        LightCore(std::string const& color);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a LightCore.
        ////////////////////////////////////////////////////////////////////////
        virtual ~LightCore();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the LightCore's name of color.
        ///
        ///\return color The color's name
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_color() const;

    private:
        std::string color_;

};

}

#endif // LIGHT_CORE_HPP
