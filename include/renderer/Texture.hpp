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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the Texture class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_TEXTURE_HPP
#define GUA_TEXTURE_HPP

// guacamole headers
#include "renderer/RenderContext.hpp"

// external headers
#include <string>
#include <vector>
#include <thread>
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
        /// This constructs a new texture with the given parameters.
        ///
        /// \param width The width of the resulting texture.
        /// \param height The height of the resulting texture.
        /// \param color_depth The color depth of the resulting
        /// texture.
        /// \param color_format The color format of the resulting
        /// texture.
        /// \param type The data type texture data is stored
        /// in.
        ////////////////////////////////////////////////////////////
        Texture(unsigned width, unsigned height,
                scm::gl::data_format color_format = scm::gl::FORMAT_RGB_32F,
                scm::gl::sampler_state_desc const& state_descripton
                = scm::gl::sampler_state_desc(scm::gl::FILTER_MIN_MAG_LINEAR));

        ////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new texture from a given file.
        ///
        /// \param file The file which contains the texture data
        ////////////////////////////////////////////////////////////
        Texture(std::string const& file,
                scm::gl::sampler_state_desc const& state_descripton
                        = scm::gl::sampler_state_desc(
                                scm::gl::FILTER_MIN_MAG_LINEAR,
                                scm::gl::WRAP_REPEAT, scm::gl::WRAP_REPEAT));

        ////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This will delete all associated buffers.
        ////////////////////////////////////////////////////////////
        virtual ~Texture();

        ////////////////////////////////////////////////////////////
        /// \brief Bind the texture.
        ///
        /// This will bind the texture to the current OpenGL context
        /// with the given layer.
        ///
        ///\param context The current context.
        ///\param texture_type The type of the texture.
        ////////////////////////////////////////////////////////////
        void bind(RenderContext const& context, int texture_type) const;

        ////////////////////////////////////////////////////////////
        /// \brief Unbind a texture.
        ///
        /// This will unbind the texture with the given position.
        /// \param texture_type The type of the texture.
        ////////////////////////////////////////////////////////////
        void unbind(RenderContext const& context);

        ////////////////////////////////////////////////////////////
        /// \brief Get the Texture-ID.
        ///
        /// \return The texture's ID
        ////////////////////////////////////////////////////////////
        scm::gl::texture_2d_ptr const& get_buffer (
                                        RenderContext const& context) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) shader program.
        ////////////////////////////////////////////////////////////////////////
        unsigned width() const;
        unsigned height() const;

    protected:
        mutable unsigned width_, height_;
        scm::gl::data_format color_format_;
        scm::gl::sampler_state_desc state_descripton_;
        mutable std::vector<scm::gl::texture_2d_ptr> textures_;
        mutable std::vector<scm::gl::sampler_state_ptr> sampler_states_;
        mutable std::mutex upload_mutex_;

        virtual void upload_to(RenderContext const& context) const;

    private:
        std::string file_name_;
};

}
# endif // GUA_TEXTURE_HPP


