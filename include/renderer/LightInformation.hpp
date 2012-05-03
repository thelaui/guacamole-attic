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
/// \brief Declaration of the RenderBackend class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_LIGHT_INFORMATION_HPP
#define GUA_LIGHT_INFORMATION_HPP

#include <string>

#include "renderer/RenderContext.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"

#define GUA_MAX_LIGHT_COUNT 64

namespace gua {

struct LightInformation {
    math::vec4 light_count;
    math::vec4 position[GUA_MAX_LIGHT_COUNT];
    math::vec4 color_radius[GUA_MAX_LIGHT_COUNT];

    static void add_block_include_string(RenderContext const& context);

    private:
        static const std::string shader_include_path_;
        static const std::string shader_include_src_;
};


}

#endif // GUA_LIGHT_INFORMATION_HPP

