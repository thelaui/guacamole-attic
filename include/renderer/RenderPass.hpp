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
/// \brief Declaration of the RenderPass class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_PASS_HPP
#define RENDER_PASS_HPP

#include <memory>
#include <string>
#include <map>

#include "renderer/FrameBufferObject.hpp"
#include "renderer/BufferDescriptions.hpp"
#include "renderer/Texture.hpp"
#include "renderer/enums.hpp"
#include "traverser/RenderMask.hpp"

namespace gua {

class RenderPipeline;

class RenderPass {
    public:
        RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& render_mask = "",
                   float width = 1.f, float height = 1.f, bool size_is_relative = true);

        void add_buffer(ColorBufferDescription const& buffer_desc);
        void add_buffer(DepthStencilBufferDescription const& buffer_desc);

        void set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                              std::string const& target_material, std::string const& target_uniform);

        void overwrite_uniform_float(std::string const& material, std::string const& uniform_name, float value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::shared_ptr<Texture> const& value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::string const& texture_name);

        std::string const& get_name() const;

        friend class RenderPipeline;
        friend class RenderBackend;

    private:
        std::shared_ptr<Texture> const& get_buffer(std::string const& name, CameraMode mode);

        void flush();
        void create_buffers(StereoMode mode);
        void create_buffer(std::map<std::string, std::shared_ptr<Texture>>& buffer_store, FrameBufferObject& fbo);
        void set_pipeline(RenderPipeline* pipeline);

        struct PassConnection {
            std::string in_render_pass, in_buffer, target_material, target_uniform;
        };

        std::vector<ColorBufferDescription> color_buffer_descriptions_;
        DepthStencilBufferDescription depth_stencil_buffer_description_;

        std::string name_, camera_, screen_;
        RenderMask render_mask_;
        float width_, height_;
        bool size_is_relative_to_window_;

        std::map<std::string, std::shared_ptr<Texture>> left_eye_buffers_, right_eye_buffers_, center_eye_buffers_;
        FrameBufferObject left_eye_fbo_, right_eye_fbo_, center_eye_fbo_;

        RenderPipeline* pipeline_;
        bool rendererd_left_eye_, rendererd_right_eye_, rendererd_center_eye_;

        std::vector<PassConnection> connections_;

        // target material    target uniform        input pass             input buffer
        std::map<std::string, std::map<std::string, std::pair<std::string, std::string>>> inputs_;

        // target material    target uniform        input buffer
        std::map<std::string, std::map<std::string, std::shared_ptr<Texture>>> texture_uniforms_;

        // target material    target uniform        input value
        std::map<std::string, std::map<std::string, float>> float_uniforms_;
};

}

#endif // RENDER_PASS_HPP


