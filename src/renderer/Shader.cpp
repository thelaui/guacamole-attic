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
/// \brief Definition of the Shader class.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/Shader.hpp"

# include <iostream>
# include <sstream>

#include "include/renderer/RenderContext.hpp"
#include "include/renderer/glInclude.hpp"
#include "include/utils/debug.hpp"

namespace gua {

Shader::Shader():
    shader_ids_(),
    shader_type_(0),
    source_(),
    data_(),
    uniforms_() {}

Shader::Shader(std::string const& file_name, unsigned shader_type):
    shader_ids_(),
    shader_type_(shader_type),
    source_(file_name),
    data_(),
    uniforms_() {

    if (!source_.is_valid()) {
        WARNING("Failed to load shader \"%s\": File does not exist!", file_name.c_str());
    } else {
        data_ = source_.get_content().c_str();
        find_uniforms();
    }
}

Shader::Shader(char const* data, unsigned shader_type):
    shader_ids_(),
    shader_type_(shader_type),
    source_(),
    data_(data) {
        find_uniforms();
}

unsigned Shader::get_id(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (shader_ids_.size() <= context.id || shader_ids_[context.id] == 0) {
        upload_to(context);
    }

    return shader_ids_[context.id];
}

std::vector<Uniform> const& Shader::get_uniforms() const{
    return uniforms_;
}

void Shader::upload_to(RenderContext const& context) const {
    if (shader_ids_.size() <= context.id) {
        shader_ids_.resize(context.id+1);
    }

    shader_ids_[context.id] = glCreateShader(shader_type_);

    glShaderSource(shader_ids_[context.id], 1, &data_, 0);
    glCompileShader(shader_ids_[context.id]);

    validate_shader(shader_ids_[context.id]);
}

void Shader::validate_shader(unsigned shader) const {
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
        WARNING("Compile log for shader file \"%s\":", source_.get_file_name().c_str());
        std::cout << buffer << std::endl;
    }
}

void Shader::find_uniforms() {
    std::stringstream shader_stream(data_);
    std::string current_string;

    while (shader_stream >> current_string) {
        if (current_string == "uniform") {
            Uniform new_uniform;
            new_uniform.location_ = 0;
            std::string type, name;
            shader_stream >> type >> name;

            if (name[name.length()-1] == ';')
                name = name.substr(0, name.length()-1);

            if (type == "mat4") {
                new_uniform.type_ = Uniform::MAT4;
                new_uniform.name_ = name;
                uniforms_.push_back(new_uniform);
            } else if (type == "vec2") {
                new_uniform.type_ = Uniform::VEC2;
                new_uniform.name_ = name;
                uniforms_.push_back(new_uniform);
            } else if (type == "vec3") {
                new_uniform.type_ = Uniform::VEC3;
                new_uniform.name_ = name;
                uniforms_.push_back(new_uniform);
            } else if (type == "vec4") {
                new_uniform.type_ = Uniform::VEC4;
                new_uniform.name_ = name;
                uniforms_.push_back(new_uniform);
            } else if (type == "sampler2D") {
                new_uniform.type_ = Uniform::SAMPLER2D;
                new_uniform.name_ = name;
                uniforms_.push_back(new_uniform);
            } else WARNING("Unknown uniform type %s!", type.c_str());
        }
    }
}

}
