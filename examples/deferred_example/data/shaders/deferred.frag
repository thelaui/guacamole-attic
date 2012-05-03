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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////

#version 420

#extension GL_ARB_shading_language_include : require

#include </gua/LightInformation.glslh>

in vec2 texcoord;
in vec3 camera_position;

uniform sampler2D tex_color;
uniform sampler2D tex_normal;
uniform sampler2D tex_specular_emit;
uniform sampler2D tex_position;

layout (location = 0) out vec3 out_color;

void main(void) {
    vec3 color = texture2D(tex_color, texcoord).rgb;
    vec3 position = texture2D(tex_position, texcoord).rgb;
    vec3 normal = texture2D(tex_normal, texcoord).rgb;
    float specular = texture2D(tex_specular_emit, texcoord).r;
    float emit = texture2D(tex_specular_emit, texcoord).g;

    out_color = vec3(0.f, 0.f, 0.f);

    for(int i=0; i<gua_light_information.light_count.x; ++i) {

        vec3 diffuse_direction = normalize(gua_light_information.position[i].xyz - position);
        float diffuse  = max(dot(diffuse_direction, normal),0.0);

        vec3 spec_direction = reflect(diffuse_direction, normal);
        float specularity = pow(max(dot(spec_direction, normalize(position - camera_position)),0.0), 100) * specular;

        float attenuation = max(1.0 - distance(position, gua_light_information.position[i].xyz)/gua_light_information.color_radius[i].a , 0.0);

        out_color += (color * diffuse + specularity) * attenuation * gua_light_information.color_radius[i].rgb;
    }

    out_color = emit * color + (1 - emit) * out_color;
}
