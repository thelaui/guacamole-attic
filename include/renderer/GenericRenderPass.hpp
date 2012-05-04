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
/// \brief Declaration of the GenericRenderPass class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_GENERIC_RENDER_PASS_HPP
#define GUA_GENERIC_RENDER_PASS_HPP

// guacamole headers
#include "renderer/FrameBufferObject.hpp"
#include "renderer/BufferDescriptions.hpp"
#include "renderer/TextRenderer.hpp"
#include "renderer/Texture.hpp"
#include "renderer/enums.hpp"
#include "traverser/RenderMask.hpp"

// external headers
#include <memory>
#include <string>
#include <map>

namespace gua {

class RenderPipeline;

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
/// A virtual base class for render passes. It has a name, manages addition of
/// buffers and provides a basic interface which has to be implemented by
/// derived classes.
///
/// Render passes are part of a rendering pipeline. Basically they encapsulate
/// some FBOs to which the scene is rendered. The user has to add some color
/// buffers to this pass and a depth stencil buffer if desired. The scene is
/// rendered frome the point of view of a given camera through a given screen.
/// With render masks a part of the scene may be hidden.
////////////////////////////////////////////////////////////////////////////////
class GenericRenderPass {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new GenericRenderPass from the given parameters.
        ///
        /// \param name             The name of this rendering pass.
        /// \param camera           The name of the camera used for this pass.
        /// \param screen           The name of the screen used for pass.
        /// \param render_mask      The rendering mask which should be applied
        ///                         to the scene before rendering this pass.
        /// \param width            The width of this pass. Either relative to
        ///                         the window size or absolute pixel size.
        /// \param height           The height of this pass. Either relative to
        ///                         the window size or absolute pixel size.
        /// \param size_is_relative Determines whether width and height are
        ///                         interpreted as abolute or as releative.
        ////////////////////////////////////////////////////////////////////////
        GenericRenderPass(std::string const& name, std::string const& camera,
                          std::string const& screen,
                          std::string const& render_mask,
                          float width, float height, bool size_is_relative);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the GenericRenderPass and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        virtual ~GenericRenderPass();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new color buffer to this pass.
        ///
        /// Adds a new color buffer to the internally used FBO.
        ///
        /// \param buffer_desc      The description of the new buffer.
        ////////////////////////////////////////////////////////////////////////
        void add_buffer(ColorBufferDescription const& buffer_desc);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new depth stencil buffer to this pass.
        ///
        /// Adds a new depth stencil buffer to the internally used FBO.
        ///
        /// \param buffer_desc      The description of the new buffer.
        ////////////////////////////////////////////////////////////////////////
        void add_buffer(DepthStencilBufferDescription const& buffer_desc);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the name of the pass.
        ///
        /// \return                 The name of this pass.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_name() const;

        friend class RenderPipeline;
        friend class RenderPass;
        friend class FullscreenPass;

    protected:
        virtual std::shared_ptr<Texture> get_buffer(std::string const& name,
                                                     CameraMode mode,
                                                     bool draw_fps = false)=0;

        void flush();
        void create_buffers(StereoMode mode);
        void create_buffer(std::map<std::string,
                           std::shared_ptr<Texture>>& buffer_store,
                           FrameBufferObject& fbo);

        void set_pipeline(RenderPipeline* pipeline);

        std::vector<ColorBufferDescription> color_buffer_descriptions_;
        DepthStencilBufferDescription depth_stencil_buffer_description_;

        std::string name_, screen_, camera_;
        RenderMask render_mask_;
        float width_, height_;
        bool size_is_relative_to_window_;

        std::map<std::string, std::shared_ptr<Texture>> left_eye_buffers_,
                                                        right_eye_buffers_,
                                                        center_eye_buffers_;

        FrameBufferObject left_eye_fbo_, right_eye_fbo_, center_eye_fbo_;

        RenderPipeline* pipeline_;
        bool rendererd_left_eye_, rendererd_right_eye_, rendererd_center_eye_;

        TextRenderer* text_renderer_;
};

}

#endif // GUA_GENERIC_RENDER_PASS_HPP



