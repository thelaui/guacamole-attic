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
/// \brief Declaration of the Shader class.
////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include "utils/TextFile.hpp"

namespace gua {

class RenderContext;

////////////////////////////////////////////////////////////////////////////////
/// \brief A base class for Fragment- and VertexShaders.
///
/// It is used to upload shader information to the GPU. It should not be
/// directly instanciated, use the derived class instead.
////////////////////////////////////////////////////////////////////////////////

class Shader {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) shader.
        ////////////////////////////////////////////////////////////////////////
        Shader();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Loads a shader from file.
        ///
        /// Loads a shader from the given glsl source file.
        ///
        /// \param file_name   The source file for this shader.
        /// \param shader_type Either GL_FRAGMENT_SHADER of GL_VERTEX_SHADER
        ////////////////////////////////////////////////////////////////////////
        Shader(std::string const& file_name, unsigned shader_type);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Loads a shader from buffer.
        ///
        /// Loads a shader from given buffer data.
        ///
        /// \param data        The data buffer for this shader.
        /// \param shader_type Either GL_FRAGMENT_SHADER of GL_VERTEX_SHADER
        ////////////////////////////////////////////////////////////////////////
        Shader(char const* data, unsigned shader_type);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Get the ID of this shader.
        ///
        /// Returns the ID of this shader for the given OpenGL context.
        ///
        /// \param context The context for which the ID should be returned.
        /// \return        The ID of the shader.
        ////////////////////////////////////////////////////////////////////////
        unsigned get_id(RenderContext const& context) const;

    private:
        void upload_to(RenderContext const& context) const;
        void validate_shader(unsigned shader) const;

        mutable std::vector<unsigned> shader_ids_;
        unsigned shader_type_;
        mutable TextFile source_;
        mutable char const* data_;
};

}

#endif // SHADER_HPP
