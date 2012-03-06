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
/// \brief Shaders for filling deferred rendering buffers.
////////////////////////////////////////////////////////////////////////////////

#ifndef BUFFER_FILL_SHADERS_HPP
#define BUFFER_FILL_SHADERS_HPP

#include <string>

namespace gua {

const std::string BUFFER_FILL_VERTEX_SHADER = {
"#version 330\n"\

"layout(location=0) in vec3 in_position;\n"\
"layout(location=1) in vec3 in_normal;\n"\
"layout(location=2) in vec2 in_texture_coord;\n"\

"uniform mat4 projection_matrix;\n"\
"uniform mat4 view_matrix;\n"\
"uniform mat4 model_matrix;\n"\
"uniform mat4 normal_matrix;\n"\

"out vec3 position;\n"\
"out vec3 normal;\n"\
"out vec2 tex_coord;\n"\

"void main() {\n"\
"	position = ((view_matrix * model_matrix) * vec4(in_position, 1.0)).xyz;\n"\
"	normal = normalize(vec3(normal_matrix * vec4(in_normal, 0.0)));\n"\
"	tex_coord = in_texture_coord;\n"\

"	gl_Position =  projection_matrix * vec4(position, 1.f);\n"\
"} \n"\

};


const std::string BUFFER_FILL_FRAGMENT_SHADER = {
"#version 330\n"\

"in vec3 position;\n"\
"in vec3 normal;\n"\
"in vec2 tex_coord;\n"\

"layout (location = 0) out vec3 out_color;\n"\
"layout (location = 1) out vec3 out_position;\n"\
"layout (location = 2) out vec3 out_normal;\n"\

"void main() {\n"\
"    out_position = position;\n"\
"    out_normal = normalize(normal);\n"\
"    out_color = vec3(tex_coord, 0);\n"\
"} \n"\

};



}

#endif //BUFFER_FILL_SHADERS_HPP

