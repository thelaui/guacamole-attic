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
/// \brief Declaration of the Texture class.
////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "renderer/RenderContext.hpp"

#include <string>
#include <vector>
#include <GL/glew.h>

namespace gua {
////////////////////////////////////////////////////////////////////
/// \brief A class representing a texture.
///
/// This class allows to load texture data from a file and bind the
/// texture to an OpenGL context.
////////////////////////////////////////////////////////////////////
class Texture {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new texture.
        ///
        ////////////////////////////////////////////////////////////
        Texture();

        ////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new texture with the given parameters.
        ///
        /// \param width        The width of the resulting texture.
        /// \param height       The height of the resulting texture.
        /// \param color_depth  The color depth of the resulting
        ///                     texture.
        /// \param color_format The color format of the resulting
        ///                     texture.
        /// \param type         The data type texture data is stored
        ///                     in.
        ////////////////////////////////////////////////////////////
        Texture(unsigned width, unsigned height, unsigned color_depth = GL_RGB32F,
                unsigned color_format = GL_RGB, unsigned type = GL_FLOAT);

        ////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new texture from a given file.
        ///
        /// \param file The file which contains the texture data
        ////////////////////////////////////////////////////////////
        Texture(std::string const& file);

        ////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This will delete all associated buffers.
        ////////////////////////////////////////////////////////////
        ~Texture();

        ////////////////////////////////////////////////////////////
        /// \brief Bind the texture.
        ///
        /// This will bind the texture to the current OpenGL context
        /// with the given layer.
        ///
        ///\param context  The current context.
        ///\param texture_type The type of the texture.
        ////////////////////////////////////////////////////////////
        void bind(RenderContext const& context, unsigned texture_type) const;

        ////////////////////////////////////////////////////////////
        /// \brief Unbind a texture.
        ///
        /// This will unbind the texture with the given position.
        /// \param texture_type The type of the texture.
        ////////////////////////////////////////////////////////////
        static void unbind(unsigned texture_type);

        ////////////////////////////////////////////////////////////
        /// \brief Set a texture parameter.
        ///
        /// This will set a texture parameter with the given value.
        ///
        /// \param parameter_name The name of the parameter.
        /// \param value          The new value of the parameter.
        ////////////////////////////////////////////////////////////
        void set_parameter(unsigned parameter_name, unsigned value) const;

        ////////////////////////////////////////////////////////////
        /// \brief Get the Texture-ID.
        ///
        /// \return The texture's ID
        ////////////////////////////////////////////////////////////
        unsigned get_id(RenderContext const& context) const;

    private:
        unsigned width_, height_, color_depth_, color_format_, type_;
        std::vector<unsigned char> data_;

        mutable std::vector<unsigned> texture_ids_;

        void upload_to(RenderContext const& context) const;
};

}
# endif //TEXTURE_HPP





