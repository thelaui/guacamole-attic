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

#include <memory>
#include <string>
#include <map>

#include "renderer/FrameBufferObject.hpp"
#include "renderer/BufferDescriptions.hpp"
#include "renderer/TextRenderer.hpp"
#include "renderer/Texture.hpp"
#include "renderer/enums.hpp"
#include "traverser/RenderMask.hpp"

namespace gua {

class RenderPipeline;

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
class GenericRenderPass {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        GenericRenderPass(std::string const& name, std::string const& camera,
                          std::string const& screen,
                          std::string const& render_mask,
                          float width, float height, bool size_is_relative);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        virtual ~GenericRenderPass();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void add_buffer(ColorBufferDescription const& buffer_desc);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void add_buffer(DepthStencilBufferDescription const& buffer_desc);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
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



