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
/// \brief Definition of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/ShaderProgram.hpp"

// guacamole headers
#include "renderer/RenderContext.hpp"
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

ShaderProgram::
ShaderProgram():
    programs_(),
    texture_offsets_(),
    upload_mutex_(),
    v_shader_(""),
    f_shader_("") {}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
create_from_files(std::string const& v_file, std::string const& f_file) {

    v_shader_ = v_file;
    f_shader_ = f_file ;
    shaders_are_files_ = true;
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
create_from_sources(std::string const& v_source, std::string const& f_source) {

    v_shader_ = v_source;
    f_shader_ = f_source ;
    shaders_are_files_ = false;
}

////////////////////////////////////////////////////////////////////////////////

ShaderProgram::
~ShaderProgram() {}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
use(RenderContext const& context) const {

    // upload to GPU if neccessary
    if (programs_.size() <= context.id || programs_[context.id] == 0) {
        upload_to(context);
    }

    context.render_context->bind_program(programs_[context.id]);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
unuse(RenderContext const& context) const {

    texture_offsets_[context.id] = 0;
    context.render_context->reset_program();
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_mat4(RenderContext const& context, std::string const& mat_name,
         math::mat4 const& mat) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(mat_name, mat);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_vec2(RenderContext const& context, std::string const& vec_name,
         math::vec2 const& vec) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_vec3(RenderContext const& context, std::string const& vec_name,
         math::vec3 const& vec) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_color3f(RenderContext const& context, std::string const& color_name,
            Color3f const& color) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(
                    color_name, math::vec3(color.r(), color.g(), color.b()));
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_vec4(RenderContext const& context, std::string const& vec_name,
         math::vec4 const& vec) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(vec_name, vec);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_sampler2D(RenderContext const& context, std::string const& sampler_name,
              Texture const& sampler) {

    if (programs_.size() > context.id) {
        sampler.bind(context, texture_offsets_[context.id]);
        programs_[context.id]->uniform(
                                    sampler_name, texture_offsets_[context.id]);
        ++texture_offsets_[context.id];
    }
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_float(RenderContext const& context, std::string const& float_name,
          float value) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(float_name, value);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
set_int(RenderContext const& context, std::string const& int_name,
        int value) {

    if (programs_.size() > context.id)
        programs_[context.id]->uniform(int_name, value);
}

////////////////////////////////////////////////////////////////////////////////

void ShaderProgram::
upload_to(RenderContext const& context) const {

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (programs_.size() <= context.id) {
        programs_.resize(context.id+1);
        texture_offsets_.resize(context.id+1);
        texture_offsets_[context.id] = 0;
    }

    if (shaders_are_files_) {
        programs_[context.id] = context.render_device->create_program({

            context.render_device->create_shader_from_file(
                                    scm::gl::STAGE_VERTEX_SHADER, v_shader_),

            context.render_device->create_shader_from_file(
                                    scm::gl::STAGE_FRAGMENT_SHADER, f_shader_)
        });
    } else {
        programs_[context.id] = context.render_device->create_program({


            context.render_device->create_shader(
                                    scm::gl::STAGE_VERTEX_SHADER, v_shader_),

            context.render_device->create_shader(
                                    scm::gl::STAGE_FRAGMENT_SHADER, f_shader_)
        });
    }

    std::cout << programs_[context.id]->info_log().c_str() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

}
