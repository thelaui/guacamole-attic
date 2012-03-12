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
/// \brief Definition of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/ShaderProgram.hpp"

#include <eigen2/Eigen/LU>

#include "renderer/VertexShader.hpp"
#include "renderer/FragmentShader.hpp"
#include "renderer/RenderContext.hpp"
#include "renderer/glInclude.hpp"

#include "utils/debug.hpp"

namespace gua {

ShaderProgram::ShaderProgram():
    program_ids_(),
    uniforms_(),
    texture_offset_(0) {}

ShaderProgram::ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader ):
    program_ids_(),
    uniforms_(),
    texture_offset_(0),
    v_shader_(v_shader),
    f_shader_(f_shader) {}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::use(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (program_ids_.size() <= context.id || program_ids_[context.id] == 0) {
        upload_to(context);
    }

    glUseProgram(program_ids_[context.id]);
}

void ShaderProgram::unuse() const {
    texture_offset_ = 0;
    glUseProgram(0);
}

void ShaderProgram::set_mat4(RenderContext const& context, std::string const& mat_name, Eigen::Matrix4f const& mat) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, mat_name, Uniform::MAT4));
        if(loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, mat.data());
    }
}

void ShaderProgram::set_vec2(RenderContext const& context, std::string const& vec_name, Eigen::Vector2f const& vec) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, vec_name, Uniform::VEC2));
        if (loc >= 0) glUniform2f(loc, vec.x(), vec.y());
    }
}

void ShaderProgram::set_vec3(RenderContext const& context, std::string const& vec_name, Eigen::Vector3f const& vec) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, vec_name, Uniform::VEC3));
        if(loc >= 0) glUniform3f(loc, vec.x(), vec.y(), vec.z());
    }
}

void ShaderProgram::set_vec3(RenderContext const& context, std::string const& vec_name, Color3f const& vec) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, vec_name, Uniform::VEC3));
        if(loc >= 0) glUniform3f(loc, vec.r(), vec.g(), vec.b());
    }
}

void ShaderProgram::set_vec4(RenderContext const& context, std::string const& vec_name, Eigen::Vector4f const& vec) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, vec_name, Uniform::VEC4));
        if(loc >= 0) glUniform4f(loc, vec[0], vec[1], vec[2], vec[3]);
    }
}

void ShaderProgram::set_sampler2D(RenderContext const& context, std::string const& sampler_name, Texture const& sampler) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, sampler_name, Uniform::SAMPLER2D));
        if(loc >= 0) {
            sampler.bind(context, texture_offset_);
            glUniform1i(loc, texture_offset_);
            ++texture_offset_;
        }
    }
}

void ShaderProgram::set_float(RenderContext const& context, std::string const& float_name, float value) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, float_name, Uniform::FLOAT));
        if(loc >= 0) glUniform1f(loc, value);
    }
}

void ShaderProgram::set_int(RenderContext const& context, std::string const& int_name, int value) const{
    if (uniforms_.size() > context.id) {
        unsigned loc(check_uniform(context, int_name, Uniform::INT));
        if(loc >= 0) glUniform1i(loc, value);
    }
}


unsigned ShaderProgram::check_uniform(RenderContext const& context, std::string const& name, Uniform::Type type) const {
    auto uniform(uniforms_[context.id].find(name));

    if (uniform == uniforms_[context.id].end()) {
        WARNING("Uniform %s does not exist on the given context!", name.c_str());
        return -1;
    } else if (uniform->second.type_ != type) {
        WARNING("Uniform %s's type does not match the given one!", name.c_str());
        return -1;
    }

    return uniform->second.location_;
}

void ShaderProgram::upload_to(RenderContext const& context) const {

    if (program_ids_.size() <= context.id) {
        program_ids_.resize(context.id+1);
        uniforms_.resize(context.id+1);
    }

    unsigned program_id = glCreateProgram();

    glAttachShader(program_id, v_shader_.get_id(context));
    glAttachShader(program_id, f_shader_.get_id(context));

    glLinkProgram(program_id);
    glValidateProgram(program_id);

    for (auto& uniform : v_shader_.get_uniforms())
        uniforms_[context.id].insert(std::make_pair(uniform.name_, uniform));
    for (auto& uniform : v_shader_.get_uniforms())
        uniforms_[context.id][uniform.name_].location_ = glGetUniformLocation(program_id, uniform.name_.c_str());

    for (auto& uniform : f_shader_.get_uniforms())
        uniforms_[context.id].insert(std::make_pair(uniform.name_, uniform));
    for (auto& uniform : f_shader_.get_uniforms())
        uniforms_[context.id][uniform.name_].location_ = glGetUniformLocation(program_id, uniform.name_.c_str());

    glBindAttribLocation(program_id, vertex_location, "in_position");
	glBindAttribLocation(program_id, normal_location, "in_normal");
	glBindAttribLocation(program_id, texture_location, "in_tex_coord");

	program_ids_[context.id] = program_id;

}

}
