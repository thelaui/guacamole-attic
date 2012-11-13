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
in mat4 inverse_projection_view_matrix;

uniform sampler2D in_normal;
uniform sampler2D in_tex_coords_mat_id;
uniform sampler2D in_depth_stencil;
uniform float texel_width;
uniform float texel_height;

layout(location=0) out vec3 diffuse;
layout(location=1) out vec3 specular;


vec3 get_world_pos(sampler2D depth_texture, vec2 frag_pos, mat4 inverse_projection_view_matrix) {
    vec2 ndc_pos = frag_pos * 2.0 - 1.0;
    float depth = texture2D(depth_texture, frag_pos).x * 2.0 - 1.0;
    vec4 screen_space_pos = vec4(ndc_pos.x , ndc_pos.y, depth, 1.0);
    vec4 h = inverse_projection_view_matrix * screen_space_pos;
    h /= h.w;
    return h.xyz;
}

void main() {
    vec2 frag_pos = vec2(gl_FragCoord.x * texel_width, gl_FragCoord.y * texel_height);

    int mat_id = int(texture2D(in_tex_coords_mat_id, frag_pos).z);

    if (mat_id == 4) {
        diffuse = vec3(0, 0, 0);
        specular = vec3(0, 0, 0);
    } else {
        vec3 world_pos = get_world_pos(in_depth_stencil, frag_pos, inverse_projection_view_matrix);

        vec3 world_normal = texture2D(in_normal, frag_pos).xyz;

        vec3 dir_to_light = out_light_position - world_pos;
        float dist_to_light = length(dir_to_light);
        dir_to_light /= dist_to_light;

        if (dist_to_light > out_light_radius)
            discard;

        if (dot(world_normal, dir_to_light) < 0)
            discard;

        float attenuation = pow(1.0 - dist_to_light/out_light_radius, 1);
        float diffuse_term = dot(world_normal, dir_to_light) * attenuation;
        float specular_term = pow(max(0, dot(reflect(dir_to_light, world_normal), normalize(world_pos - out_camera_position))) , 50) * attenuation;

        diffuse = vec3(1, 1, 1) * diffuse_term;
        specular = vec3(1, 1, 1) * specular_term;
    }
}
