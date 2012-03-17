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

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 normal_matrix;

out vec3 light_position;
out float light_radius;

void main() {
    light_position = vec4(model_matrix * vec4(0.f, 0.f, 0.f, 1.0)).xyz;
    light_radius = length(vec4(model_matrix * vec4(in_position, 1.0)).xyz - light_position);

    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1.0);
}
