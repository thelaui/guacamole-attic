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

#include <GL/gl.h>

namespace gua {

FrameBufferObject::FrameBufferObject():
    fbos_() {}

FrameBufferObject::~FrameBufferObject() {
    for (auto fbo: fbos_)
        if (fbo)
            glDeleteFramebuffers(1, &fbo);
}

void FrameBufferObject::attach_buffer(RenderContext const& context,
                                      unsigned buffer_type, unsigned buffer_id, unsigned attachment_id,
                                      int mip_level, int z_slice) {
    bind(context, {});

    switch (buffer_type) {
        case GL_TEXTURE_1D:
            glFramebufferTexture1D(GL_FRAMEBUFFER, attachment_id, GL_TEXTURE_1D, buffer_id, mip_level);
            break;
        case GL_TEXTURE_2D_ARRAY:
            glFramebufferTexture(GL_FRAMEBUFFER, attachment_id, buffer_id, z_slice);
            break;
        case GL_TEXTURE_3D:
            glFramebufferTexture3D(GL_FRAMEBUFFER, attachment_id, GL_TEXTURE_3D, buffer_id, mip_level, z_slice);
            break;
        default:
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_id, buffer_type, buffer_id, mip_level);
            break;
    }

    unbind();
}

void FrameBufferObject::bind(RenderContext const& context,
                             std::vector<unsigned> const& attachments) {
    // upload to GPU if neccessary
    if (fbos_.size() <= context.id || fbos_[context.id] == 0) {
        upload_to(context);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, fbos_[context.id]);

    if (attachments.size() > 0)
        glDrawBuffers(attachments.size(), &(*attachments.begin()));
}

void FrameBufferObject::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::upload_to(RenderContext const& context) const {
    if (fbos_.size() <= context.id) {
        fbos_.resize(context.id+1);
    }

    unsigned fbo_id(0);
    glGenFramebuffers(1, &fbo_id);
    fbos_[context.id] = fbo_id;
}

}




