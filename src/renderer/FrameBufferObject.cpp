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
/// \brief A class to maintain OpenGL's FBOs.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/FrameBufferObject.hpp"

#include "renderer/RenderContext.hpp"
#include "utils/debug.hpp"

#include <GL/glew.h>
#include <string>

namespace gua {

FrameBufferObject::FrameBufferObject():
    fbos_() {}

FrameBufferObject::~FrameBufferObject() {
}

void FrameBufferObject::attach_color_buffer(RenderContext const& context, unsigned in_color_attachment, Texture const& buffer,
                                            int mip_level, int z_slice) {
    if (fbos_.size() <= context.id) {
        fbos_.resize(context.id+1);
        fbos_[context.id] = context.render_device->create_frame_buffer();
    }

    fbos_[context.id]->attach_color_buffer(in_color_attachment, buffer.get_buffer(context), mip_level, z_slice);
}

void FrameBufferObject::attach_depth_stencil_buffer(RenderContext const& context, Texture const& buffer,
                                                    int mip_level, int z_slice) {
    if (fbos_.size() <= context.id) {
        fbos_.resize(context.id+1);
        fbos_[context.id] = context.render_device->create_frame_buffer();
    }

    fbos_[context.id]->attach_depth_stencil_buffer(buffer.get_buffer(context), mip_level, z_slice);
}

void FrameBufferObject::bind(RenderContext const& context) {
    if (context.id < fbos_.size())
        context.render_context->set_frame_buffer(fbos_[context.id]);
}

void FrameBufferObject::unbind(RenderContext const& context) {
    if (fbos_.size() > context.id && fbos_[context.id] != 0)
        context.render_context->reset_framebuffer();
}

}




