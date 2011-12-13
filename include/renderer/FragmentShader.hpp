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
/// \brief Declaration of the FragmentShader class.
////////////////////////////////////////////////////////////////////////////////

#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include "include/renderer/Shader.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief A Fragment Shader abstraction.
///
/// Can be used to load a fragment shader from file.
////////////////////////////////////////////////////////////////////////////////

class FragmentShader: public Shader {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) FragmentShader. Use the other constructor in
        /// order to retrieve a useful shader object.
        ////////////////////////////////////////////////////////////////////////
        FragmentShader();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from source file.
        ///
        /// This constructor will create a new FragmentShader object. It is
        /// loaded from a given glsl source file.
        ///
        /// \param file The glsl source file.
        ////////////////////////////////////////////////////////////////////////
        FragmentShader( std::string const& file );
};

#endif // FRAGMENTSHADER_HPP

