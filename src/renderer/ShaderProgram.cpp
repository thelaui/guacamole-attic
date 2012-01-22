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
    glUseProgram(0);
}

void ShaderProgram::set_mat4(RenderContext const& context, std::string const& mat_name, Eigen::Matrix4f const& mat) {
    if (uniforms_[mat_name].size() > context.id)
        glUniformMatrix4fv(uniforms_[mat_name][context.id].location_, 1, GL_FALSE, mat.data());
}

void ShaderProgram::set_vec2(RenderContext const& context, std::string const& vec_name, Eigen::Vector2f const& vec) {
    if (uniforms_[vec_name].size() > context.id)
        glUniform2f(uniforms_[vec_name][context.id].location_, vec.x(), vec.y());
}

void ShaderProgram::set_vec3(RenderContext const& context, std::string const& vec_name, Eigen::Vector3f const& vec) {
    if (uniforms_[vec_name].size() > context.id)
        glUniform3f(uniforms_[vec_name][context.id].location_, vec.x(), vec.y(), vec.z());
}

void ShaderProgram::set_vec4(RenderContext const& context, std::string const& vec_name, Eigen::Vector4f const& vec) {
    if (uniforms_[vec_name].size() > context.id)
        glUniform4f(uniforms_[vec_name][context.id].location_, vec[0], vec[1], vec[2], vec[3]);
}

void ShaderProgram::set_sampler2d(RenderContext const& context, std::string const& sampler_name, Texture const& sampler) {
    if (uniforms_[sampler_name].size() > context.id) {
        sampler.bind(context, GL_TEXTURE0 + texture_offset_);

        unsigned sampler_location(glGetUniformLocation(program_ids_[context.id], sampler_name.c_str()));
        glUniform1i(sampler_location, texture_offset_);

        ++texture_offset_;
    }
}

void ShaderProgram::set_projection_matrix(RenderContext const& context, Eigen::Matrix4f const& projection_matrix) const {
    if (projection_matrix_.size() > context.id)
        glUniformMatrix4fv(projection_matrix_[context.id].location_, 1, GL_FALSE, projection_matrix.data());
}

void ShaderProgram::set_view_matrix(RenderContext const& context, Eigen::Matrix4f const& view_matrix) const {
    if (view_matrix_.size() > context.id)
        glUniformMatrix4fv(view_matrix_[context.id].location_, 1, GL_FALSE, view_matrix.data());
}

void ShaderProgram::set_model_matrix(RenderContext const& context, Eigen::Matrix4f const& model_matrix) const {
    if (model_matrix_.size() > context.id && normal_matrix_.size() > context.id ) {
        Eigen::Matrix4f normal_matrix(model_matrix.inverse().transpose());
        glUniformMatrix4fv(model_matrix_[context.id].location_, 1, GL_FALSE, model_matrix.data());
        glUniformMatrix4fv(normal_matrix_[context.id].location_, 1, GL_FALSE, normal_matrix.data());
    }
}

void ShaderProgram::upload_to(RenderContext const& context) const {

    if (program_ids_.size() <= context.id) {
        program_ids_.resize(context.id+1);
        projection_matrix_.resize(context.id+1);
        view_matrix_.resize(context.id+1);
        model_matrix_.resize(context.id+1);
        normal_matrix_.resize(context.id+1);
    }

    unsigned program_id = glCreateProgram();

    glAttachShader(program_id, v_shader_.get_id(context));
    glAttachShader(program_id, f_shader_.get_id(context));

	glBindFragDataLocation(program_id, GL_COLOR_ATTACHMENT0, "out_position");
	glBindFragDataLocation(program_id, GL_COLOR_ATTACHMENT0+1, "out_normal");
    glBindFragDataLocation(program_id, GL_COLOR_ATTACHMENT0+2, "out_color");

    glLinkProgram(program_id);
    glValidateProgram(program_id);

    projection_matrix_[context.id].location_ = glGetUniformLocation(program_id, "projection_matrix");
    view_matrix_[context.id].location_ = glGetUniformLocation(program_id, "view_matrix");
    model_matrix_[context.id].location_ = glGetUniformLocation(program_id, "model_matrix");
    normal_matrix_[context.id].location_ = glGetUniformLocation(program_id, "normal_matrix");
    unsigned diffuse_loc = glGetUniformLocation(program_id, "diffuse");
    glUniform1i(diffuse_loc, 0);

    glBindAttribLocation(program_id, vertex_location, "in_position");
	glBindAttribLocation(program_id, normal_location, "in_normal");
	glBindAttribLocation(program_id, texture_location, "in_tex_coord");

	program_ids_[context.id] = program_id;

}

}
