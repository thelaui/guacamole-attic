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

#ifndef STEREO_SHADERS_HPP
#define STEREO_SHADERS_HPP

#include <string>

namespace gua {

const std::string STEREO_VERTEX_SHADER = {
"#version 330\n"\

"layout(location=0) in vec3 in_position;\n"\

"out vec2 tex_coord;\n"\

"void main() {\n"\
"	tex_coord = in_position.xy*0.5 + 0.5;\n"\
"	gl_Position = vec4(in_position, 1.0);\n"\
"} \n"\

};


const std::string STEREO_FRAGMENT_SHADER = {
"#version 330\n"\

"in vec2 tex_coord;\n"\

"uniform sampler2D right_tex;\n"\
"uniform sampler2D left_tex;\n"\

"uniform int mode;\n"\

"layout (location = 0) out vec4 out_color;\n"\

"void main() {\n"\
"    if (mode == 0) { //MONO \n"\
"        out_color = vec4(texture2D( left_tex, tex_coord).rgb, 1.0);\n"\
"    } else if (mode == 1) { //SIDE_BY_SIDE\n"\
"        if (tex_coord.x < 0.5) {\n"\
"            out_color = vec4(texture2D( left_tex, vec2(tex_coord.x*2, tex_coord.y)).rgb, 1.0);\n"\
"        } else {\n"\
"            out_color = vec4(texture2D( right_tex, vec2(tex_coord.x*2-1, tex_coord.y)).rgb, 1.0);\n"\
"        }\n"\
"    } else if (mode == 2) { //ANAGLYPH_RED_GREEN\n"\
"        out_color = vec4(texture2D( left_tex, tex_coord).r, texture2D( right_tex, tex_coord).g, 0, 1.0);\n"\
"    } else { // ANAGLYPH_RED_CYAN\n"\
"        out_color = vec4(texture2D( left_tex, tex_coord).r, texture2D( right_tex, tex_coord).gb, 1.0);\n"\
"    }\n"\

"} \n"\

};



}

#endif //STEREO_SHADERS_HPP

