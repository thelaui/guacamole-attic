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
/// \brief A class to easily load, bind and undbind textures.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/WarpMatrix.hpp"
#include "utils/debug.hpp"

#include <fstream>

namespace gua {

WarpMatrix::WarpMatrix():
    Texture(0, 0),
    data_() {}

WarpMatrix::WarpMatrix(std::string const& file_name):
                 Texture(0, 0, scm::gl::FORMAT_RGBA_32F, scm::gl::sampler_state_desc(scm::gl::FILTER_MIN_MAG_LINEAR)),
                 data_() {

    std::ifstream file (file_name, std::ios::binary);

    if (file) {

        file.read((char*) &width_, sizeof(unsigned));
        file.read((char*) &height_, sizeof(unsigned));

        // shared_array<math::vec4f> img_data;
        // file.read(img_data.get(), w * h * sizeof(math::vec4f));

        // std::vector<void*> mip_data;
        // mip_data.push_back(imag_data.get());

        // device->create_texture_2d(....)

        data_ = std::vector<float>(sizeof(float)*width_*height_*4);
        unsigned index(0);
        for(unsigned i(0); i < width_ * height_; ++i){
            float u, v, intensity, dummy;
            file.read((char*) &u, sizeof(float));
            file.read((char*) &v, sizeof(float));
            file.read((char*) &intensity, sizeof(float));
            file.read((char*) &dummy, sizeof(float));

            data_[index++] = u;
            data_[index++] = v;
            data_[index++] = intensity;
            data_[index++] = dummy;
        }

        file.close();
    } else {
        WARNING ("Unable to load Warpmatrix! File %s does not exist.", file_name.c_str());
    }

}

WarpMatrix::~WarpMatrix() {

}

void WarpMatrix::upload_to(RenderContext const& context) const{

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (textures_.size() <= context.id) {
        textures_.resize(context.id + 1);
        sampler_states_.resize(context.id + 1);
    }

    std::vector<void*> tmp_data;
    tmp_data.push_back(&data_[0]);

    textures_[context.id] = context.render_device->create_texture_2d(scm::gl::texture_2d_desc(scm::math::vec2ui(width_, height_), color_format_),
                                                                     color_format_, tmp_data);

    sampler_states_[context.id] = context.render_device->create_sampler_state(state_descripton_);
}

}

