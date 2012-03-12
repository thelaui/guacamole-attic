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

"out vec2 tex_coord;\n"\

"void main() {\n"\
"	tex_coord = in_position.xy*0.5 + 0.5;\n"\
"	gl_Position = vec4(in_position, 1.0);\n"\
"} \n"\

};


const std::string BUFFER_FILL_FRAGMENT_SHADER = {
"#version 330\n"\

"in vec2 tex_coord;\n"\
"uniform sampler2D tex;\n"\

"layout (location = 0) out vec4 out_color;\n"\

"void main() {\n"\
"    out_color = vec4(texture2D( tex, tex_coord).rgb, 1.0);\n"\
"} \n"\

};



}

#endif //BUFFER_FILL_SHADERS_HPP

