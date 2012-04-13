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
/// \brief Definition of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/ShaderProgram.hpp"

#include "renderer/RenderContext.hpp"
#include "renderer/glInclude.hpp"

#include "utils/debug.hpp"

namespace gua {

ShaderProgram::ShaderProgram():
    programs_(),
    texture_offset_(0),
    v_shader_(""),
    f_shader_("") {}

void ShaderProgram::create_from_files(std::string const& v_shader_file, std::string const& f_shader_file) {
    v_shader_ = v_shader_file;
    f_shader_ = f_shader_file ;
    shaders_are_files_ = true;
}

void ShaderProgram::create_from_sources(std::string const& v_shader_source, std::string const& f_shader_source) {
    v_shader_ = v_shader_source;
    f_shader_ = f_shader_source ;
    shaders_are_files_ = false;
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::use(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (programs_.size() <= context.id || programs_[context.id] == 0) {
        upload_to(context);
    }

    context.render_context->bind_program(programs_[context.id]);
}

void ShaderProgram::unuse(RenderContext const& context) const {
    texture_offset_ = 0;
    context.render_context->reset_program();
}

void ShaderProgram::set_mat4(RenderContext const& context, std::string const& mat_name, math::mat4 const& mat) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(mat_name, mat);
}

void ShaderProgram::set_vec2(RenderContext const& context, std::string const& vec_name, math::vec2 const& vec) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

void ShaderProgram::set_vec3(RenderContext const& context, std::string const& vec_name, math::vec3 const& vec) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

void ShaderProgram::set_color3f(RenderContext const& context, std::string const& color_name, Color3f const& color) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(color_name, math::vec3(color.r(), color.g(), color.b()));
}

void ShaderProgram::set_vec4(RenderContext const& context, std::string const& vec_name, math::vec4 const& vec) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

void ShaderProgram::set_sampler2D(RenderContext const& context, std::string const& sampler_name, Texture const& sampler) {
    if (programs_.size() > context.id) {
        sampler.bind(context, texture_offset_);
        programs_[context.id]->uniform(sampler_name, texture_offset_);
        ++texture_offset_;
    }
}

void ShaderProgram::set_float(RenderContext const& context, std::string const& float_name, float value) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(float_name, value);
}

void ShaderProgram::set_int(RenderContext const& context, std::string const& int_name, int value) {
    if (programs_.size() > context.id)
        programs_[context.id]->uniform(int_name, value);
}

void ShaderProgram::upload_to(RenderContext const& context) const {
    if (programs_.size() <= context.id) {
        programs_.resize(context.id+1);
    }

    if (shaders_are_files_) {
        programs_[context.id] = context.render_device->create_program({
            context.render_device->create_shader_from_file(scm::gl::STAGE_VERTEX_SHADER, v_shader_),
            context.render_device->create_shader_from_file(scm::gl::STAGE_FRAGMENT_SHADER, f_shader_)
        });
    } else {
        programs_[context.id] = context.render_device->create_program({
            context.render_device->create_shader(scm::gl::STAGE_VERTEX_SHADER, v_shader_),
            context.render_device->create_shader(scm::gl::STAGE_FRAGMENT_SHADER, f_shader_)
        });
    }

    std::cout << programs_[context.id]->info_log().c_str() << std::endl;
}

}
