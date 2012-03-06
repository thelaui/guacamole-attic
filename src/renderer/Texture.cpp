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
/// \brief A class to easily load, bind and undbind textures.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/Texture.hpp"

#include "utils/debug.hpp"

#include <scm/gl_util/imaging/texture_loader.h>
#include <iostream>

namespace gua {

Texture::Texture(unsigned width, unsigned height, scm::gl::data_format color_format,
                 scm::gl::sampler_state_desc const& state_descripton):
                 width_(width),
                 height_(height),
                 color_format_(color_format),
                 file_name_(""),
                 state_descripton_(state_descripton),
                 textures_(),
                 sampler_states_() {}

Texture::Texture(std::string const& file, scm::gl::sampler_state_desc const& state_descripton):
    width_(0),
    height_(0),
    color_format_(scm::gl::FORMAT_NULL),
    file_name_(file),
    state_descripton_(state_descripton),
    textures_(),
    sampler_states_() {}

Texture::~Texture() {}

void Texture::bind(RenderContext const& context, unsigned texture_type) const {
    if (textures_.size() <= context.id || textures_[context.id] == 0)
        upload_to(context);

    context.render_context->bind_texture(textures_[context.id], sampler_states_[context.id], texture_type);
}

void Texture::unbind(RenderContext const& context, unsigned texture_type) {
    if (textures_.size() > context.id && textures_[context.id] != 0)
        context.render_context->reset_texture_units();
}

scm::gl::texture_2d_ptr const& Texture::get_buffer(RenderContext const& context) const {
    if (textures_.size() <= context.id || textures_[context.id] == 0)
        upload_to(context);

    return textures_[context.id];
}

void Texture::upload_to(RenderContext const& context) const{

    if (textures_.size() <= context.id) {
        textures_.resize(context.id + 1);
        sampler_states_.resize(context.id + 1);
    }

    if (file_name_ == "") {
        textures_[context.id] = context.render_device->create_texture_2d(scm::math::vec2ui(width_, height_), color_format_);
    } else {
        scm::gl::texture_loader loader;
        textures_[context.id] = loader.load_texture_2d(*context.render_device, file_name_, false);
    }

    sampler_states_[context.id] = context.render_device->create_sampler_state(state_descripton_);
}

}
