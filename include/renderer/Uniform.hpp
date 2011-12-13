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
/// \brief Declaration of the Uniform struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef UNIFORM_HPP
#define UNIFORM_HPP

////////////////////////////////////////////////////////////////////////////////
/// \brief A struct with information on a uniform.
///
/// Stores information on a uniform on one context.
////////////////////////////////////////////////////////////////////////////////

struct Uniform {
    ////////////////////////////////////////////////////////////////////////////
    /// \brief
    ////////////////////////////////////////////////////////////////////////////
    enum Type { FLOAT, INT, BOOL, VEC2, VEC3, VEC4, MAT2, MAT3, MAT4 };

    ////////////////////////////////////////////////////////////////////////////
    /// \brief
    ////////////////////////////////////////////////////////////////////////////
    Type type_;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief
    ////////////////////////////////////////////////////////////////////////////
    unsigned location_;
};

#endif // UNIFORM_HPP

