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
/// \brief Declaration of the FrameBufferObject class.
////////////////////////////////////////////////////////////////////////////////

# ifndef FRAMEBUFFEROBJECT_HPP
# define FRAMEBUFFEROBJECT_HPP

#include <vector>

#include "renderer/Texture.hpp"
#include "utils/Color3f.hpp"

namespace gua {

class RenderContext;

////////////////////////////////////////////////////////////////////
/// \brief A class representing a FrameBufferObject.
///
/// This class allows to load texture data from a file and bind the
/// texture to an OpenGL context.
////////////////////////////////////////////////////////////////////
class FrameBufferObject {
    public:

        ////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new FrameBufferObject.
        ////////////////////////////////////////////////////////////
        FrameBufferObject();

        ////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This will delete all associated buffers.
        ////////////////////////////////////////////////////////////
        ~FrameBufferObject();

        ////////////////////////////////////////////////////////////
        /// \brief Attaches a buffer to the FrameBufferObject.
        ///
        /// This will attach a buffer to the FrameBufferObject.
        ///
        /// \param context The RenderContext to bind to.
        /// \param buffer_type   The GL-type of the buffer
        ///                     (e.g. GL_TEXTURE_2D).
        /// \param buffer_id     The buffer's id.
        /// \param attachment_id The buffer's attachment id.
        /// \param mip_level     The buffer's mip_level.
        /// \param z_slice       The buffer's z_slice.
        ////////////////////////////////////////////////////////////
        void attach_color_buffer(RenderContext const& context, unsigned in_color_attachment, Texture const& buffer,
                                 int mip_level = 0, int z_slice = 0);

        void attach_depth_stencil_buffer(RenderContext const& context, Texture const& buffer,
                                         int mip_level = 0, int z_slice = 0);

        void clear_color_buffers(RenderContext const& context, Color3f const& clear_color = Color3f());
        void clear_depth_stencil_buffer(RenderContext const& context);

        ////////////////////////////////////////////////////////////
        /// \brief Bind the FrameBufferObject.
        ///
        /// This will bind a FrameBufferObject to the current
        /// OpenGL context.
        ///
        /// \param context The RenderContext to bind to.
        /// \param attachment_id The id of the attachment to be bound.
        ////////////////////////////////////////////////////////////
        void bind(RenderContext const& context);

        ////////////////////////////////////////////////////////////
        /// \brief Unbind the FrameBufferObject.
        ///
        /// This will unbind the FrameBufferObject.
        ////////////////////////////////////////////////////////////
        void unbind(RenderContext const& context);

    private:
        mutable std::vector<scm::gl::frame_buffer_ptr> fbos_;
};

}

# endif //FRAMEBUFFEROBJECT_HPP






