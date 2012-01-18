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

#include <IL/il.h>
#include <iostream>

namespace gua {

Texture::Texture():
    width_(0),
    height_(0),
    color_depth_(0),
    color_format_(0),
    type_(0),
    data_(NULL),
    texture_ids_() {}

Texture::Texture(unsigned width, unsigned height, unsigned color_depth,
                 unsigned color_format, unsigned type):
                 width_(width),
                 height_(height),
                 color_depth_(color_depth),
                 color_format_(color_format),
                 type_(type),
                 data_(NULL),
                 texture_ids_() {}

Texture::Texture(std::string const& file):
    width_(0),
    height_(0),
    color_depth_(0),
    color_format_(0),
    type_(0),
    data_(NULL),
    texture_ids_() {

    ILuint image_id (0);
    ilGenImages(1, &image_id);
    ilBindImage(image_id);

    if (!ilLoadImage(file.c_str()))
        ERROR("Failed to load texture %s!", file.c_str());

    data_ = ilGetData();
    width_ = ilGetInteger(IL_IMAGE_WIDTH);
    height_ = ilGetInteger(IL_IMAGE_HEIGHT);
    color_depth_ = GL_RGB;
    color_format_ = GL_RGB;
    type_ = (GL_UNSIGNED_BYTE);

    ilBindImage(0);
    ilDeleteImage(image_id);
}

Texture::~Texture() {
    for (auto texture_id : texture_ids_)
        if (texture_id) {
            glBindTexture(GL_TEXTURE_2D, 0);
            glDeleteTextures(1, &texture_id);
        }
}

void Texture::bind(RenderContext const& context, unsigned layer_position) const {
    if (texture_ids_.size() <= context.id || texture_ids_[context.id] == 0)
        upload_to(context);

    glActiveTexture(GL_TEXTURE0 + layer_position);
    glBindTexture(GL_TEXTURE_2D, texture_ids_[context.id]);
}

void Texture::unbind(unsigned texture_position) {
    glActiveTexture(GL_TEXTURE0 + texture_position);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned Texture::get_id(RenderContext const& context) const {
    return texture_ids_[context.id];
}

void Texture::set_parameter(unsigned parameter_name, unsigned value) const {
    glTexParameteri(GL_TEXTURE_2D, parameter_name, value);
}

void Texture::upload_to(RenderContext const& context) const{


    // generate texture id
    unsigned texture_id(0);
    glGenTextures(1, &texture_id);
    if (texture_id == 0) {
        // OpenGL was not able to generate additional texture
        return;
    }

    if (texture_ids_.size() <= context.id)
        texture_ids_.resize(context.id + 1);

    texture_ids_[context.id] = texture_id;

    glEnable(GL_TEXTURE_2D);
    // bind texture object
    glBindTexture(GL_TEXTURE_2D, texture_ids_[context.id]);
    // load data as texture
    glTexImage2D(GL_TEXTURE_2D, 0, color_depth_, width_, height_,
                 0, color_format_, type_, data_);

    //setting Texture Parameters
    set_parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    set_parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
    set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP);

}

}
