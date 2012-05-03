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
/// \brief Declaration and implementation of the BufferDescription
///       structs.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_BUFFER_DESCRIPTIONS_HPP
#define GUA_BUFFER_DESCRIPTIONS_HPP

#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
struct ColorBufferDescription {
    ColorBufferDescription(std::string const& name, unsigned location,
                           scm::gl::data_format format = scm::gl::data_format(
                                                      scm::gl::FORMAT_RGB_16F)):
        name_(name),
        location_(location),
        format_(format) {}

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pre-loads some Materials.
    ////////////////////////////////////////////////////////////////////////////
    std::string name_;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pre-loads some Materials.
    ////////////////////////////////////////////////////////////////////////////
    unsigned location_;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pre-loads some Materials.
    ////////////////////////////////////////////////////////////////////////////
    scm::gl::data_format format_;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
struct DepthStencilBufferDescription {
    DepthStencilBufferDescription(std::string const& name,
                      scm::gl::data_format format = scm::gl::data_format(
                                                          scm::gl::FORMAT_D16)):
        name_(name),
        format_(format) {}

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pre-loads some Materials.
    ////////////////////////////////////////////////////////////////////////////
    std::string name_;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Pre-loads some Materials.
    ////////////////////////////////////////////////////////////////////////////
    scm::gl::data_format format_;
};

}

#endif // GUA_BUFFER_DESCRIPTIONS_HPP



