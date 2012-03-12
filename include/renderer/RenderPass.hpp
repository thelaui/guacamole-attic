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
#include "renderer/Texture.hpp"

namespace gua {

class RenderPipeline;

class RenderPass {
    public:
        struct ColorBufferDescription {
            ColorBufferDescription(std::string n, unsigned loc,
                              float w = 1.f, float h = 1.f, bool size_is_relative = true,
                              unsigned clr_depth = GL_RGB32F, unsigned clr_format = GL_RGB, unsigned t = GL_FLOAT):
                              name(n),
                              location(loc),
                              width(w),
                              height(h),
                              size_is_relative_to_window(size_is_relative),
                              color_depth(clr_depth ),
                              color_format(clr_format),
                              type(t) {}
            std::string name;
            unsigned location;
            float width, height;
            bool size_is_relative_to_window;
            unsigned color_depth, color_format, type;
        };

        struct DepthStencilBufferDescription {
            DepthStencilBufferDescription(std::string n,
                              float w = 1.f, float h = 1.f, bool size_is_relative = true,
                              unsigned clr_depth = GL_DEPTH_COMPONENT32, unsigned clr_format = GL_DEPTH_COMPONENT, unsigned t = GL_FLOAT):
                              name(n),
                              width(w),
                              height(h),
                              size_is_relative_to_window(size_is_relative),
                              color_depth(clr_depth ),
                              color_format(clr_format),
                              type(t) {}
            std::string name;
            float width, height;
            bool size_is_relative_to_window;
            unsigned color_depth, color_format, type;
        };

        RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& entry_point);

        void add_buffer(ColorBufferDescription const& buffer_desc);
        void add_buffer(DepthStencilBufferDescription const& buffer_desc);

        void set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                              std::string const& target_material, std::string const& target_uniform);

        void overwrite_uniform_float(std::string const& material, std::string const& uniform_name, float value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::shared_ptr<Texture> const& value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::string const& texture_name);

        std::string const& get_name() const;

        friend class RenderPipeline;

    private:
        std::shared_ptr<Texture> const& get_buffer(std::string const& name);

        void flush();
        void create_buffers();
        void set_pipeline(RenderPipeline* pipeline);

        struct PassConnection {
            std::string in_render_pass, in_buffer, target_material, target_uniform;
        };

        std::vector<ColorBufferDescription> color_buffer_descriptions_;
        DepthStencilBufferDescription depth_stencil_buffer_description_;

        std::string name_, camera_, screen_, entry_point_;
        std::map<std::string, std::shared_ptr<Texture>> buffers_;
        FrameBufferObject fbo_;
        RenderPipeline* pipeline_;
        bool rendered_frame_;

        std::vector<PassConnection> connections_;

        std::map<std::string, std::map<std::string, std::shared_ptr<Texture>>> texture_uniforms_;
        std::map<std::string, std::map<std::string, float>> float_uniforms_;
};

}

#endif // RENDER_PASS_HPP


