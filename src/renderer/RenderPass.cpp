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
/// \brief Implementation of the RenderPass class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/RenderPass.hpp"

#include "renderer/RenderPipeline.hpp"
#include "renderer/RenderBackend.hpp"
#include "renderer/TextureBase.hpp"
#include "traverser/Optimizer.hpp"

namespace gua {

RenderPass::RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& entry_point):
    color_buffer_descriptions_(),
    depth_stencil_buffer_description_(""),
    name_(name),
    camera_(camera),
    screen_(screen),
    entry_point_(entry_point),
    buffers_(),
    fbo_(),
    pipeline_(NULL),
    rendered_frame_(false),
    connections_(),
    texture_uniforms_(),
    float_uniforms_() {}

void RenderPass::add_buffer(ColorBufferDescription const& buffer_desc) {
    color_buffer_descriptions_.push_back(buffer_desc);
}

void RenderPass::add_buffer(DepthStencilBufferDescription const& buffer_desc) {
    depth_stencil_buffer_description_ = buffer_desc;
}

void RenderPass::set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                                  std::string const& target_material, std::string const& target_uniform) {

}

void RenderPass::overwrite_uniform_float(std::string const& material, std::string const& uniform_name, float value) {
    float_uniforms_[material][uniform_name] = value;
}

void RenderPass::overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::shared_ptr<Texture> const& value) {
    texture_uniforms_[material][uniform_name] = value;
}

void RenderPass::overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::string const& texture_name) {
    texture_uniforms_[material][uniform_name] = TextureBase::instance()->get(texture_name);
}

std::string const& RenderPass::get_name() const {
    return name_;
}

std::shared_ptr<Texture> const& RenderPass::get_buffer(std::string const& name) {
    if (rendered_frame_)
        return buffers_[name];

    Optimizer optimizer;
    optimizer.check(pipeline_->get_current_graph());

    RenderBackend renderer;
    renderer.render(camera_, screen_, optimizer.get_data(), fbo_, pipeline_->get_context());

    rendered_frame_ = true;

    return buffers_[name];
}

void RenderPass::flush() {
    rendered_frame_ = false;
}

void RenderPass::create_buffers() {
    buffers_.clear();
    fbo_ = FrameBufferObject();

    if (depth_stencil_buffer_description_.name != "") {
        int width = depth_stencil_buffer_description_.size_is_relative_to_window ? depth_stencil_buffer_description_.width*pipeline_->get_context().width :
                                                         depth_stencil_buffer_description_.width;
        int height = depth_stencil_buffer_description_.size_is_relative_to_window ? depth_stencil_buffer_description_.height*pipeline_->get_context().height :
                                                             depth_stencil_buffer_description_.height;

        std::shared_ptr<Texture> new_buffer(new Texture(width, height,
                                                        depth_stencil_buffer_description_.color_depth, depth_stencil_buffer_description_.color_format,
                                                        depth_stencil_buffer_description_.type));

        new_buffer->set_parameter(GL_TEXTURE_COMPARE_MODE, GL_NONE);
        new_buffer->set_parameter(GL_DEPTH_TEXTURE_MODE, GL_ALPHA);

        fbo_.attach_buffer(pipeline_->get_context(), GL_TEXTURE_2D, new_buffer->get_id(pipeline_->get_context()), GL_DEPTH_ATTACHMENT);
        buffers_[depth_stencil_buffer_description_.name] = new_buffer;
    }

    for (auto& description: color_buffer_descriptions_) {
        int width = description.size_is_relative_to_window ? description.width*pipeline_->get_context().width :
                                                             description.width;
        int height = description.size_is_relative_to_window ? description.height*pipeline_->get_context().height :
                                                             description.height;

        std::shared_ptr<Texture> new_buffer(new Texture(width, height,
                                                        description.color_depth, description.color_format,
                                                        description.type));
        fbo_.attach_buffer(pipeline_->get_context(), GL_TEXTURE_2D, new_buffer->get_id(pipeline_->get_context()), GL_COLOR_ATTACHMENT0 + description.location);
        buffers_[description.name] = new_buffer;
    }
}

void RenderPass::set_pipeline(RenderPipeline* pipeline) {
    pipeline_ = pipeline;
}

}



