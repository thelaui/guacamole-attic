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
/// \brief A database for accessing material data.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/ShaderProgram.hpp"

#include "include/renderer/VertexShader.hpp"
#include "include/renderer/FragmentShader.hpp"
#include "include/renderer/glInclude.hpp"

ShaderProgram::ShaderProgram():
    program_id_(0) {}

ShaderProgram::ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader ):
    program_id_(0) {

    program_id_ = glCreateProgram();

    glAttachShader(program_id_, v_shader.get_id());
    glAttachShader(program_id_, f_shader.get_id());

    glLinkProgram(program_id_);
}

ShaderProgram::~ShaderProgram() {}

void ShaderProgram::use() const {
    glUseProgram(program_id_);
}
