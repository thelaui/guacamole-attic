////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
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
/// \brief Definition of the Texture class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/Texture.hpp"

// guacamole headers
#include "utils/debug.hpp"
#include "utils/math.hpp"

// external headers
#include <scm/gl_util/data/imaging/texture_loader.h>
#include <iostream>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

Texture::
Texture(unsigned width, unsigned height, scm::gl::data_format color_format,
     scm::gl::sampler_state_desc const& state_descripton):
     width_(width),
     height_(height),
     color_format_(color_format),
     file_name_(""),
     state_descripton_(state_descripton),
     textures_(),
     sampler_states_(),
     upload_mutex_() {}

////////////////////////////////////////////////////////////////////////////////

Texture::
Texture(std::string const& file,
        scm::gl::sampler_state_desc const& state_descripton):
    width_(0),
    height_(0),
    color_format_(scm::gl::FORMAT_NULL),
    file_name_(file),
    state_descripton_(state_descripton),
    textures_(),
    sampler_states_(),
    upload_mutex_() {}

////////////////////////////////////////////////////////////////////////////////

Texture::~Texture() {}

////////////////////////////////////////////////////////////////////////////////

void Texture::
bind(RenderContext const& context, int position) const {

    if (textures_.size() <= context.id || textures_[context.id] == 0)
        upload_to(context);

    context.render_context->bind_texture(
              textures_[context.id], sampler_states_[context.id], position);
}

////////////////////////////////////////////////////////////////////////////////

void Texture::
unbind(RenderContext const& context) {

    if (textures_.size() > context.id && textures_[context.id] != 0)
        context.render_context->reset_texture_units();
}

////////////////////////////////////////////////////////////////////////////////

scm::gl::texture_2d_ptr const& Texture::
get_buffer(RenderContext const& context) const {

    if (textures_.size() <= context.id || textures_[context.id] == 0)
        upload_to(context);

    return textures_[context.id];
}

////////////////////////////////////////////////////////////////////////////////

unsigned Texture::
width() const {

    return width_;
}

////////////////////////////////////////////////////////////////////////////////

unsigned Texture::
height() const {

    return height_;
}

////////////////////////////////////////////////////////////////////////////////

void Texture::
upload_to(RenderContext const& context) const{

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (textures_.size() <= context.id) {
        textures_.resize(context.id + 1);
        sampler_states_.resize(context.id + 1);
    }

    if (file_name_ == "") {
        textures_[context.id] = context.render_device->create_texture_2d(
                                    math::vec2ui(width_, height_),
                                    color_format_);
    } else {
        scm::gl::texture_loader loader;
        textures_[context.id] = loader.load_texture_2d(
                                    *context.render_device, file_name_, true);

        if(textures_[context.id]) {
            width_  = textures_[context.id]->dimensions()[0];
            height_ = textures_[context.id]->dimensions()[1];
        }
    }

    sampler_states_[context.id] = context.render_device->create_sampler_state(
                                    state_descripton_);
}

////////////////////////////////////////////////////////////////////////////////

}
