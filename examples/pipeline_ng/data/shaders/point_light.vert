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
layout(location=1) in vec3 in_texcoord;
layout(location=2) in vec3 in_normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

out vec3 out_position;
out vec3 out_camera_position;
out vec3 out_light_position;
out float out_light_radius;
out mat4 inverse_view_matrix;

void main() {
	out_position = (model_matrix * vec4(in_position, 1.0)).xyz;
    out_light_position = (model_matrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
    out_light_radius = length(out_light_position - out_position);
	gl_Position = projection_matrix * view_matrix * vec4(out_position, 1.0);    
    inverse_view_matrix = inverse(view_matrix);
    out_camera_position = (inverse_view_matrix * vec4(0.0, 0.0, 0.0, 1.0)).xyz;
}
