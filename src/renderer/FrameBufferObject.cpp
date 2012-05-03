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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief A class to maintain Schism's FBOs.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/FrameBufferObject.hpp"

#include "renderer/RenderContext.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"

#include <GL/glew.h>
#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

FrameBufferObject::
FrameBufferObject():
    fbos_(), upload_mutex_(), width_(0), height_(0) {}

////////////////////////////////////////////////////////////////////////////////

FrameBufferObject::
~FrameBufferObject() {}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
attach_color_buffer(RenderContext const& ctx, unsigned in_color_attachment,
                    Texture const& buffer, int mip_level, int z_slice) {

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (set_size(buffer)) {
        if (fbos_.size() <= ctx.id) {
            fbos_.resize(ctx.id+1);
            fbos_[ctx.id] = ctx.render_device->create_frame_buffer();
        }

        fbos_[ctx.id]->attach_color_buffer(
                            in_color_attachment, buffer.get_buffer(ctx),
                            mip_level, z_slice);
    }
}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
attach_depth_stencil_buffer(RenderContext const& ctx, Texture const& buffer,
                            int mip_level, int z_slice) {

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (set_size(buffer)) {
        if (fbos_.size() <= ctx.id) {
            fbos_.resize(ctx.id+1);
            fbos_[ctx.id] = ctx.render_device->create_frame_buffer();
        }

        fbos_[ctx.id]->attach_depth_stencil_buffer(
                                    buffer.get_buffer(ctx), mip_level, z_slice);
    }
}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
clear_color_buffers(RenderContext const& ctx, Color3f const& color) {

    if (ctx.id < fbos_.size())
        ctx.render_context->clear_color_buffers(
                                fbos_[ctx.id], math::vec4(color.r(), color.g(),
                                                          color.b(), 0.f));
}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
clear_depth_stencil_buffer(RenderContext const& ctx) {

    if (ctx.id < fbos_.size())
        ctx.render_context->clear_depth_stencil_buffer(fbos_[ctx.id]);
}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
bind(RenderContext const& ctx) {

    if (ctx.id < fbos_.size())
        ctx.render_context->set_frame_buffer(fbos_[ctx.id]);
}

////////////////////////////////////////////////////////////////////////////////

void FrameBufferObject::
unbind(RenderContext const& ctx) {

    if (fbos_.size() > ctx.id && fbos_[ctx.id] != 0)
        ctx.render_context->reset_framebuffer();
}

////////////////////////////////////////////////////////////////////////////////

unsigned FrameBufferObject::
width() const {

    return width_;
}

////////////////////////////////////////////////////////////////////////////////

unsigned FrameBufferObject::
height() const {

    return height_;
}

////////////////////////////////////////////////////////////////////////////////

bool FrameBufferObject::
set_size(Texture const& buffer) {

    if (width_ == 0 && height_ == 0) {
        width_ = buffer.width();
        height_ = buffer.height();
        return true;
    } else if (buffer.width() != width_ || buffer.height() != height_) {
        WARNING("Buffers attached to the same FrameBufferObject must have the \
                same size!");

        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

}
