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
#include "renderer/TextureBase.hpp"

namespace gua {

RenderPass::RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& entry_point):
    name_(name),
    camera_(camera),
    screen_(screen),
    entry_point_(entry_point),
    buffers_(),
    fbo_(),
    pipeline_(NULL),
    connections_(),
    texture_uniforms_(),
    float_uniforms_() {}

void RenderPass::add_color_buffer(std::string const& buffer_name, unsigned layout_location, BufferDescription const& buffer_desc) {
    std::shared_ptr<Texture> new_buffer(new Texture(buffer_desc.width, buffer_desc.height,
                                                    buffer_desc.color_depth, buffer_desc.color_format,
                                                    buffer_desc.type));
    fbo_.attach_buffer(pipeline_->get_context(), GL_TEXTURE_2D, new_buffer->get_id(pipeline_->get_context()), GL_COLOR_ATTACHMENT0 + layout_location);
    buffers_[buffer_name] = new_buffer;
}

void RenderPass::add_depth_stencil_buffer(std::string const& buffer_name, BufferDescription const& buffer_desc) {
    std::shared_ptr<Texture> new_buffer(new Texture(buffer_desc.width, buffer_desc.height,
                                                    buffer_desc.color_depth, buffer_desc.color_format,
                                                    buffer_desc.type));
    fbo_.attach_buffer(pipeline_->get_context(), GL_TEXTURE_2D, new_buffer->get_id(pipeline_->get_context()), GL_DEPTH_ATTACHMENT);
    buffers_[buffer_name] = new_buffer;
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
    return buffers_[name];
}

void RenderPass::flush() {

}

void RenderPass::set_pipeline(RenderPipeline* pipeline) {
    pipeline_ = pipeline;
}

}



