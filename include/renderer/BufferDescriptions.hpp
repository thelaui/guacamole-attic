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
/// \brief Declaration and implementation of the BufferDescription
///       structs.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_BUFFER_DESCRIPTIONS_HPP
#define GUA_BUFFER_DESCRIPTIONS_HPP

#include <string>

namespace gua {

struct ColorBufferDescription {
    ColorBufferDescription(std::string const& n, unsigned loc,
                           scm::gl::data_format form = scm::gl::data_format(scm::gl::FORMAT_RGB_16F)):
                      name(n),
                      location(loc),
                      format(form) {}
    std::string name;
    unsigned location;
    scm::gl::data_format format;
};

struct DepthStencilBufferDescription {
    DepthStencilBufferDescription(std::string const& n,
                      scm::gl::data_format form = scm::gl::data_format(scm::gl::FORMAT_D16)):
                      name(n),
                      format(form) {}
    std::string name;
    scm::gl::data_format format;
};

}

#endif // GUA_BUFFER_DESCRIPTIONS_HPP



