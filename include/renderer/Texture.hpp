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

#include <string>
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
        ///\param layer_position The position of the layer.
        ////////////////////////////////////////////////////////////
        void bind(unsigned layer_position) const;

        ////////////////////////////////////////////////////////////
        /// \brief Unbind a texture.
        ///
        /// This will unbind the texture with the given position.
        /// \param texture_position Position of the texture.
        ////////////////////////////////////////////////////////////
        static void unbind(unsigned texture_position);

        ////////////////////////////////////////////////////////////
        /// \brief Get the textures id.
        ///
        /// This returns the textures id on the current context.
        /// \return texture_id The texture's id.
        ////////////////////////////////////////////////////////////
        unsigned get_id() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set a texture parameter.
        ///
        /// This will set a texture parameter with the given value.
        ///
        /// \param parameter_name The name of the parameter.
        /// \param value          The new value of the parameter.
        ////////////////////////////////////////////////////////////
        void set_parameter(unsigned parameter_name, unsigned value);

    private:
        unsigned width_, height_, texture_id_;
        GLvoid* data_;

        void generate_texture(unsigned width, unsigned height, unsigned color_depth = GL_RGB32F,
                              unsigned color_format = GL_RGB, unsigned type = GL_FLOAT);
};

}
# endif //TEXTURE_HPP





