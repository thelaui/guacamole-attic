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
/// \brief Definition of the LightInformation class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/LightInformation.hpp"

// guacamole headers
#include "utils/string_utils.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

void LightInformation::
add_block_include_string(RenderContext const& ctx) {

    if (!ctx.render_device->add_include_string(shader_include_path_,
                                               shader_include_src_)) {

        WARNING("Error adding light information block include string.");
    }
}

////////////////////////////////////////////////////////////////////////////////

const std::string LightInformation::
shader_include_path_ = "/gua/LightInformation.glslh";

////////////////////////////////////////////////////////////////////////////////

const std::string LightInformation::
shader_include_src_ =   " \
    #ifndef GUA_LIGHT_INFORMATION_INCLUDED                                  \n\
    #define GUA_LIGHT_INFORMATION_INCLUDED                                  \n\
                                                                            \n\
    layout(std140, column_major, binding=0)                                 \n\
    uniform GuaLightInformation {                                           \n\
        vec4 light_count;                                                   \n\
        vec4 position["+string_utils::to_string(GUA_MAX_LIGHT_COUNT)+"];    \n\
        vec4 color_radius["+string_utils::to_string(GUA_MAX_LIGHT_COUNT)+"];\n\
    } gua_light_information;                                                \n\
    uniform int gua_light_count;                                            \n\
                                                                            \n\
    #endif // GUA_LIGHT_INFORMATION_INCLUDED                                \n";

////////////////////////////////////////////////////////////////////////////////

}

