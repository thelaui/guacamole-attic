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
/// \brief Declaration of the LightCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_LIGHT_CORE_HPP
#define GUA_LIGHT_CORE_HPP

#include "scenegraph/Core.hpp"

#include "utils/Color3f.hpp"

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
        /// This constructs a LightCore with the given parameters and calls
        /// the constructor of base class Core with the type LIGHT.
        ///
        ///\param color   The light's color.
        ////////////////////////////////////////////////////////////////////////
        LightCore(Color3f const& color);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a LightCore.
        ////////////////////////////////////////////////////////////////////////
        virtual ~LightCore();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the LightCore's color.
        ///
        ///\return color The light's color.
        ////////////////////////////////////////////////////////////////////////
        Color3f const& get_color() const;

    private:
        Color3f color_;
};

}

#endif // GUA_LIGHT_CORE_HPP
