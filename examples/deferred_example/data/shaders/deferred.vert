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
////////////////////////////////////////////////////////////////////////////////

#version 330

layout(location=0) in vec3 in_position;
layout(location=2) in vec2 in_texcoord;

uniform mat4 view_matrix;

out vec2 texcoord;
out vec3 camera_position;

void main() {
    texcoord = in_texcoord;
    camera_position = (inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    gl_Position = vec4(in_position, 1.0);
}
