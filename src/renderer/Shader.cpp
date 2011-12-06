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

#include "include/renderer/Shader.hpp"

# include <iostream>
# include <fstream>
# include <stdio.h>
# include <stdlib.h>
# include <cstring>

#include "include/renderer/glInclude.hpp"
#include "include/utils/fileUtils.hpp"

Shader::Shader(std::string const& fileName, unsigned shaderType):
    shader_id_(0) {

    const char* glsl_source;

	glsl_source = fileUtils::text_file_read(fileName);

	shader_id_ = glCreateShader(shaderType);

	glShaderSource(shader_id_, 1, &glsl_source, 0);
	glCompileShader(shader_id_);
	validate_shader(shader_id_);
}

Shader::~Shader() {}

unsigned Shader::get_id() const {
    return shader_id_;
}

void Shader::validate_shader(unsigned shader, const char* file) {
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
    if (length > 0) {
        std::cerr << "Shader " << shader << " (" << (file?file:"") << ") compile Log: " << buffer << std::endl;
    }
}
