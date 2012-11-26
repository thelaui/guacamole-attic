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
/// \brief Declaration of the FrameBufferObject class.
////////////////////////////////////////////////////////////////////////////////

# ifndef FRAMEBUFFEROBJECT_HPP
# define FRAMEBUFFEROBJECT_HPP

// guacamole headers
#include "renderer/Texture.hpp"
#include "utils/Color3f.hpp"

// external headers
#include <mutex>
#include <vector>

namespace gua {

class RenderContext;

////////////////////////////////////////////////////////////////////////////////
/// \brief A class representing a FrameBufferObject.
///
/// This class allows to bind textures to a FBO. This FBO
/// can be used as drawing target for an rendering context.
////////////////////////////////////////////////////////////////////////////////
class FrameBufferObject {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new FrameBufferObject.
        ////////////////////////////////////////////////////////////////////////
        FrameBufferObject();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This will delete all associated buffers.
        ////////////////////////////////////////////////////////////////////////
        ~FrameBufferObject();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Attaches a color buffer to the FrameBufferObject.
        ///
        /// This will attach a buffer to the FrameBufferObject.
        ///
        /// \param context              The RenderContext to bind to.
        /// \param in_color_attachment  The buffer's attachment id.
        /// \param buffer               The texture to bind.
        /// \param mip_level            The buffer's mip_level.
        /// \param z_slice              The buffer's z_slice.
        ////////////////////////////////////////////////////////////////////////
        void attach_color_buffer(RenderContext const& context,
                                 unsigned in_color_attachment,
                                 Texture const& buffer,
                                 int mip_level = 0, int z_slice = 0);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Attaches a depth stencil buffer to the FrameBufferObject.
        ///
        /// This will attach a buffer to the FrameBufferObject.
        ///
        /// \param context              The RenderContext to bind to.
        /// \param buffer               The texture to bind.
        /// \param mip_level            The buffer's mip_level.
        /// \param z_slice              The buffer's z_slice.
        ////////////////////////////////////////////////////////////////////////
        void attach_depth_stencil_buffer(RenderContext const& context,
                                         Texture const& buffer,
                                         int mip_level = 0, int z_slice = 0);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Clears all associated color buffers.
        ///
        /// All color buffers are set to the given color. Black if no
        /// argument is given.
        ///
        /// \param context              The RenderContext to bind to.
        /// \param clear_color          The color used for clearing.
        ////////////////////////////////////////////////////////////////////////
        void clear_color_buffers(RenderContext const& context,
                                 Color3f const& clear_color = Color3f());

        ////////////////////////////////////////////////////////////////////////
        /// \brief Clears the depth stencil buffer.
        ///
        /// \param context              The RenderContext to bind to.
        ////////////////////////////////////////////////////////////////////////
        void clear_depth_stencil_buffer(RenderContext const& context);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Bind the FrameBufferObject.
        ///
        /// This will bind a FrameBufferObject to the current
        /// OpenGL context.
        ///
        /// \param context The RenderContext to bind to.
        ////////////////////////////////////////////////////////////////////////
        void bind(RenderContext const& context);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Unbind the FrameBufferObject.
        ///
        /// This will unbind the FrameBufferObject.
        ///
        /// \param context The RenderContext to bind to.
        ////////////////////////////////////////////////////////////////////////
        void unbind(RenderContext const& context);

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the size of the FrameBufferObject.
        ////////////////////////////////////////////////////////////////////////
        unsigned width() const;
        unsigned height() const;
        ///@}

    private:
        bool set_size(Texture const& buffer);

        unsigned width_, height_;
        mutable std::vector<scm::gl::frame_buffer_ptr> fbos_;
        mutable std::mutex upload_mutex_;
};

}

# endif // GUA_FRAMEBUFFEROBJECT_HPP



