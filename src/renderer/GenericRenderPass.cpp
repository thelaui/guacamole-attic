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
/// \brief Definition of the GenericRenderPass class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/GenericRenderPass.hpp"

// guacamole headers
#include "renderer/RenderPipeline.hpp"
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

GenericRenderPass::
GenericRenderPass(std::string const& name, std::string const& camera,
                  std::string const& screen, std::string const& render_mask,
                  float width, float height, bool size_is_relative):
    color_buffer_descriptions_(),
    depth_stencil_buffer_description_(""),
    name_(name),
    screen_(screen),
    camera_(camera),
    render_mask_(render_mask),
    width_(width),
    height_(height),
    size_is_relative_to_window_(size_is_relative),
    left_eye_buffers_(), right_eye_buffers_(), center_eye_buffers_(),
    left_eye_fbo_(), right_eye_fbo_(), center_eye_fbo_(),
    pipeline_(NULL),
    rendererd_left_eye_(false),
    rendererd_right_eye_(false),
    rendererd_center_eye_(false),
    text_renderer_(NULL) {}

////////////////////////////////////////////////////////////////////////////////

GenericRenderPass::
~GenericRenderPass() {

    if (text_renderer_) delete text_renderer_;
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
add_buffer(ColorBufferDescription const& desc) {

    color_buffer_descriptions_.push_back(desc);
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
add_buffer(DepthStencilBufferDescription const& desc) {

    depth_stencil_buffer_description_ = desc;
}

////////////////////////////////////////////////////////////////////////////////

std::string const& GenericRenderPass::
get_name() const {

    return name_;
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
flush() {

    rendererd_left_eye_ = false;
    rendererd_right_eye_ = false;
    rendererd_center_eye_ = false;
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
create_buffers(StereoMode mode) {

    if (mode == MONO) {
        create_buffer(center_eye_buffers_, center_eye_fbo_);
    } else {
        create_buffer(left_eye_buffers_, left_eye_fbo_);
        create_buffer(right_eye_buffers_, right_eye_fbo_);
    }
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
create_buffer(std::map<std::string, std::shared_ptr<Texture>>& buffer_store,
              FrameBufferObject& fbo) {

    buffer_store.clear();

    int width = size_is_relative_to_window_ ?
                 width_*pipeline_->get_context().width : width_;
    int height = size_is_relative_to_window_ ?
                 height_*pipeline_->get_context().height : height_;

    if (size_is_relative_to_window_
        && pipeline_->get_stereo_mode() == SIDE_BY_SIDE) width *= 0.5;

    for (auto& description: color_buffer_descriptions_) {
        Texture* new_buffer(new Texture(width, height, description.format));

        buffer_store[description.name] = std::shared_ptr<Texture>(new_buffer);

        fbo.attach_color_buffer(pipeline_->get_context(), description.location,
                                *new_buffer);
    }

    if (depth_stencil_buffer_description_.name != "") {
        Texture* new_buffer(new Texture(width, height,
                                     depth_stencil_buffer_description_.format));

        buffer_store[depth_stencil_buffer_description_.name] =
                                           std::shared_ptr<Texture>(new_buffer);

        fbo.attach_depth_stencil_buffer(pipeline_->get_context(), *new_buffer);
    }
}

////////////////////////////////////////////////////////////////////////////////

void GenericRenderPass::
set_pipeline(RenderPipeline* pipeline) {

    pipeline_ = pipeline;
}

////////////////////////////////////////////////////////////////////////////////

}
