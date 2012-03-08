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

#include "scenegraph/Iterator.hpp"
#include "renderer/FrameBufferObject.hpp"

namespace gua {

class RenderPass {
    public:
        struct BufferDescription {
            BufferDescription(float w = 1.f, float h = 1.f, bool size_is_relative = true,
                              unsigned clr_depth = GL_RGB32F, unsigned clr_format = GL_RGB, unsigned t = GL_FLOAT):
                              width(w),
                              height(h),
                              size_is_relative_to_window(size_is_relative),
                              color_depth(clr_depth ),
                              color_format(clr_format),
                              type(t) {}

            float width, height;
            bool size_is_relative_to_window;
            unsigned color_depth, color_format, type;
        };

        RenderPass(std::string const& name, std::string const& camera, std::string const& screen, SceneGraph::Iterator const& entry_point);

        void add_color_buffer(std::string const& buffer_name, unsigned layout_location, BufferDescription const& buffer_desc = BufferDescription());
        void add_depth_stencil_buffer(std::string const& buffer_name, BufferDescription const& buffer_desc = BufferDescription());

        void set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                              std::string const& target_material, std::string const& target_uniform);

        void overwrite_uniform_float(std::string const& material, std::string const& uniform_name, float value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::shared_ptr<Texture> const& value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::string const& texture_name);

        friend class RenderPipeline;

    private:
        std::shared_ptr<Texture> const& get_buffer(std::string const& name) const;

        struct PassConnection {
            std::string in_render_pass, in_buffer, target_material, target_uniform;
        };

        std::string name_, camera_, screen_;
        SceneGraph::Iterator entry_point_;
        std::map<std::string, std::shared_ptr<Texture>> buffers_;
        FrameBufferObject fbo_;

        std::vector<PassConnection> connections_;

        std::map<std::string, std::map<std::string, std::shared_ptr<Texture>>> texture_uniforms_;
        std::map<std::string, std::map<std::string, float>> float_uniforms_;
};

}

#endif // RENDER_PASS_HPP


