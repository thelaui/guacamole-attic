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
/// \brief Declaration of the LightInformation struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_LIGHT_INFORMATION_HPP
#define GUA_LIGHT_INFORMATION_HPP

#include <string>

#include "renderer/RenderContext.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"

#define GUA_MAX_LIGHT_COUNT 64

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
struct LightInformation {

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The X window associated with this context.
    ////////////////////////////////////////////////////////////////////////////
    math::vec4 light_count;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The X window associated with this context.
    ////////////////////////////////////////////////////////////////////////////
    math::vec4 position[GUA_MAX_LIGHT_COUNT];

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The X window associated with this context.
    ////////////////////////////////////////////////////////////////////////////
    math::vec4 color_radius[GUA_MAX_LIGHT_COUNT];

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Destructor.
    ///
    /// Deletes the Material and frees all associated data.
    ////////////////////////////////////////////////////////////////////////////
    static void add_block_include_string(RenderContext const& context);

    private:
        static const std::string shader_include_path_;
        static const std::string shader_include_src_;
};


}

#endif // GUA_LIGHT_INFORMATION_HPP

