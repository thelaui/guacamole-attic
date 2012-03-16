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
/// \brief Declaration and implementation of the BufferDescription structs.
////////////////////////////////////////////////////////////////////////////////

#ifndef BUFFER_DESCRIPTIONS_HPP
#define BUFFER_DESCRIPTIONS_HPP

#include <string>

namespace gua {

struct ColorBufferDescription {
    ColorBufferDescription(std::string n, unsigned loc,
                      unsigned clr_depth = GL_RGB32F, unsigned clr_format = GL_RGB, unsigned t = GL_FLOAT):
                      name(n),
                      location(loc),
                      color_depth(clr_depth ),
                      color_format(clr_format),
                      type(t) {}
    std::string name;
    unsigned location;
    unsigned color_depth, color_format, type;
};

struct DepthStencilBufferDescription {
    DepthStencilBufferDescription(std::string n,
                      unsigned clr_depth = GL_DEPTH24_STENCIL8, unsigned clr_format = GL_DEPTH_COMPONENT, unsigned t = GL_FLOAT):
                      name(n),
                      color_depth(clr_depth ),
                      color_format(clr_format),
                      type(t) {}
    std::string name;
    unsigned color_depth, color_format, type;
};

}

#endif // BUFFER_DESCRIPTIONS_HPP



