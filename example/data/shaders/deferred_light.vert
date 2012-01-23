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
////////////////////////////////////////////////////////////////////////////////

#version 330

layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_normal;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

out vec3 position;
out vec3 normal;
out vec3 light_position_camera_space;
out float light_radius;

void main() {
    position = ((view_matrix * model_matrix) * vec4(in_position, 1.0)).xyz;
	normal = normalize(vec3(normal_matrix * vec4(in_normal, 0.0)));

	light_position_camera_space = (view_matrix * model_matrix * vec4(0.f, 0.f, 0.f, 1.0)).xyz;
	light_radius = length(position - light_position_camera_space);

	gl_Position = projection_matrix * vec4(position, 1.0);
}

