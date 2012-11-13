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
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////

#version 330

layout(location=0) in vec3 in_position;
layout(location=2) in vec2 in_texcoord;

uniform mat4 view_matrix;

out vec2 out_texcoord;
out vec3 out_camera_position;

void main() {
	out_texcoord = in_texcoord;
	gl_Position = vec4(in_position, 1.0);
    out_camera_position = (inverse(view_matrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
}
