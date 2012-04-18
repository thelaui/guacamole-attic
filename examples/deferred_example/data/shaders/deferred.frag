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

in vec3 light_position;
in float light_radius;

uniform sampler2D tex_color;
uniform sampler2D tex_normal;
uniform sampler2D tex_specular;
uniform sampler2D tex_position;

uniform mat4 view_matrix;
uniform float texel_width;
uniform float texel_height;
uniform float x_fragment_offset;

layout (location = 0) out vec4 out_color;

void main(void) {
    vec2 screen_tex_coords = vec2(gl_FragCoord.s*texel_width - x_fragment_offset, gl_FragCoord.t*texel_height);

    vec4 fragment_color = vec4(texture2D(tex_color, screen_tex_coords).rgb, 1.0);
    vec3 fragment_position = texture2D(tex_position, screen_tex_coords).rgb;
    vec3 fragment_normal = texture2D(tex_normal, screen_tex_coords).rgb;

    vec3 fragment_to_light = light_position - fragment_position;

    if ( length(fragment_to_light) > light_radius) {
        discard;
    }

    vec3 fragment_to_light_direction = normalize(fragment_to_light);

    if ( dot(fragment_normal, fragment_to_light_direction) < 0) {
        discard;
    }

    vec4 diffuse_color = vec4(dot(fragment_normal, fragment_to_light_direction));

    vec3 reflection_dir = normalize(reflect(-fragment_to_light_direction, fragment_normal));
    vec3 camera_direction = normalize((inverse(view_matrix) * vec4(0.0, 0.0, .0, 1.0)).xyz - fragment_position);

    float specular = max(0, pow(dot(reflection_dir, camera_direction), 80))*texture2D(tex_specular, screen_tex_coords).r;

    float attenuation = 1.0 - (length(fragment_to_light) / (light_radius));

    out_color = fragment_color * attenuation * diffuse_color + specular * attenuation;
}
