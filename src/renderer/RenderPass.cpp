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
#include "utils/debug.hpp"

namespace gua {

RenderPass::RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& render_mask,
                       float width, float height, bool size_is_relative):
    color_buffer_descriptions_(),
    depth_stencil_buffer_description_(""),
    name_(name),
    camera_(camera),
    screen_(screen),
    render_mask_(render_mask),
    width_(width),
    height_(height),
    size_is_relative_to_window_(size_is_relative),
    left_eye_buffers_(), right_eye_buffers_(), center_eye_buffers_(),
    left_eye_fbo_(), right_eye_fbo_(), center_eye_fbo_(),
    pipeline_(NULL),
    rendererd_left_eye_(false), rendererd_right_eye_(false), rendererd_center_eye_(false) {}

void RenderPass::add_buffer(ColorBufferDescription const& buffer_desc) {
    color_buffer_descriptions_.push_back(buffer_desc);
}

void RenderPass::add_buffer(DepthStencilBufferDescription const& buffer_desc) {
    depth_stencil_buffer_description_ = buffer_desc;
}

void RenderPass::set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                                  std::string const& target_material, std::string const& target_uniform) {
    inputs_[target_material][target_uniform] = std::make_pair(in_render_pass, in_buffer);
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

std::shared_ptr<Texture> const& RenderPass::get_buffer(std::string const& name, CameraMode mode) {
    if (mode == CENTER && rendererd_center_eye_)
        return center_eye_buffers_[name];

    if (mode == LEFT && rendererd_left_eye_)
        return left_eye_buffers_[name];

    if (mode == RIGHT && rendererd_right_eye_)
        return right_eye_buffers_[name];

    Optimizer optimizer;
    optimizer.check(pipeline_->get_current_graph(), render_mask_);

    for (auto& node: optimizer.get_data().nodes_) {
        auto material(inputs_.find(node.material_));

        if (material != inputs_.end()) {
            for (auto& uniform: material->second) {
                overwrite_uniform_texture(material->first, uniform.first,
                                          pipeline_->get_render_pass(uniform.second.first)->get_buffer(uniform.second.second, mode));
            }
        }
    }

    RenderBackend renderer(this);
    renderer.render(optimizer.get_data(), pipeline_->get_context(), mode);

    if (mode == CENTER) {
        rendererd_center_eye_ = true;
        return center_eye_buffers_[name];
    } else if (mode == LEFT) {
        rendererd_left_eye_ = true;
        return left_eye_buffers_[name];
    } else {
        rendererd_right_eye_ = true;
        return right_eye_buffers_[name];
    }
}

void RenderPass::flush() {
    rendererd_left_eye_ = false;
    rendererd_right_eye_ = false;
    rendererd_center_eye_ = false;
}

void RenderPass::create_buffers(StereoMode mode) {
    switch(mode) {
        case MONO:
            create_buffer(center_eye_buffers_, center_eye_fbo_);
            break;
        default:
            create_buffer(left_eye_buffers_, left_eye_fbo_);
            create_buffer(right_eye_buffers_, right_eye_fbo_);
            break;
    }
}

void RenderPass::create_buffer(std::map<std::string, std::shared_ptr<Texture>>& buffer_store, FrameBufferObject& fbo) {
    buffer_store.clear();

    int width = size_is_relative_to_window_ ? width_*pipeline_->get_context().width : width_;
    int height = size_is_relative_to_window_ ? height_*pipeline_->get_context().height : height_;

    if (size_is_relative_to_window_ && pipeline_->get_stereo_mode() == SIDE_BY_SIDE)
        width *= 0.5;

    for (auto& description: color_buffer_descriptions_) {
        Texture* new_buffer(new Texture(width, height, description.format));

        buffer_store[description.name] = std::shared_ptr<Texture>(new_buffer);

        fbo.attach_color_buffer(pipeline_->get_context(), description.location,
                                *new_buffer);

    }

    if (depth_stencil_buffer_description_.name != "") {
        Texture* new_buffer(new Texture(width, height,
                                        depth_stencil_buffer_description_.format));

        buffer_store[depth_stencil_buffer_description_.name] = std::shared_ptr<Texture>(new_buffer);

        fbo.attach_depth_stencil_buffer(pipeline_->get_context(), *new_buffer);
    }
}

void RenderPass::set_pipeline(RenderPipeline* pipeline) {
    pipeline_ = pipeline;
}

}



