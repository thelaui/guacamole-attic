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

namespace gua {

Texture::Texture(unsigned width, unsigned height, unsigned color_depth,
                 unsigned color_format, unsigned type):
                 width_(width),
                 height_(height),
                 tex_id_(0),
                 data_(NULL) {

    // generate texture id
    glGenTextures(1, &tex_id_);

    if (tex_id_ == 0) {
        // OpenGL was not able to generate additional texture
        return;
    }

    glEnable(GL_TEXTURE_2D);
    // bind texture object
    glBindTexture(GL_TEXTURE_2D, tex_id_);
    // load data as texture
    glTexImage2D(GL_TEXTURE_2D, 0, color_depth, width, height,
                 0, color_format, type, data_);
}

Texture::Texture(std::string const& file):
    tex_id_(0) {

    ILuint imageID (0);
    ilGenImages(1, &imageID);
    ilBindImage(imageID);

    if (!ilLoadImage(file.c_str()))
        ERROR("Failed to load texture %s!", file.c_str());

    data_ = ilGetData();
    Texture(ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), GL_RGB,
            GL_RGB, GL_UNSIGNED_BYTE);

    //setting Texture Parameters
    set_parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    set_parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
    set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP);

    ilBindImage(0);
    ilDeleteImage(imageID);
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &tex_id_);
}

void Texture::bind(unsigned layer_position) {
    glActiveTexture(GL_TEXTURE0 + layer_position);
    glBindTexture(GL_TEXTURE_2D, tex_id_);
}

void Texture::unbind(unsigned texture_position) {
    glActiveTexture(GL_TEXTURE0 + texture_position);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::set_parameter(unsigned parameter_name, unsigned value) {
    glTexParameteri(GL_TEXTURE_2D, parameter_name, value);
}

}

