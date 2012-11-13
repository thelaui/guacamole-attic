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

#version 420

in vec3 out_position;
in vec3 out_camera_position;
in vec3 out_light_position;
in float out_light_radius;
in mat4 inverse_view_matrix;

uniform sampler2D in_normal;
uniform sampler2D in_tex_coords_mat_id;
uniform sampler2D in_depth_stencil;
uniform float texel_width;
uniform float texel_height;

layout(location=0) out vec3 diffuse;
layout(location=1) out vec3 specular;

void main() {
    float z_near = 0.1;
    float z_far = 100000.0;
    vec2 texcoords = vec2(gl_FragCoord.s * texel_width, gl_FragCoord.t * texel_height);
    vec4 depth_sample = texture2D(in_depth_stencil, texcoords);

    float depth = z_near * z_far / (z_far - depth_sample.x * (z_far - z_near));
    
    float aspect_ratio = texel_height / texel_width;
    vec3 view_pos = depth * vec3(texcoords.s * 2.0 - 1.0, (texcoords.t * 2.0 - 1.0) / aspect_ratio, -1.0);
    vec3 world_pos = (inverse_view_matrix * vec4(view_pos, 1.0)).xyz;

    diffuse = world_pos;    
    specular = vec3(0, 0, 0);
}
