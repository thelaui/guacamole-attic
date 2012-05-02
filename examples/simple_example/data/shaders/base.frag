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

#version 420

#extension GL_ARB_shading_language_include : require

#include </gua/LightInformation.glslh>

in vec3 normal;
in vec3 position;
in vec3 camera_position;
in vec2 texcoord;

uniform float shinyness;
uniform float emit;
uniform sampler2D tex;

layout(location=0) out vec3 out_color;

void main() {

    vec3 tex_color = texture2D(tex, texcoord).rgb;

    out_color = tex_color * emit;

    for(int i=0; i<gua_light_information.light_count.x; ++i) {
        vec3 diffuse_direction = normalize(gua_light_information.position[i].xyz - position);
        float diffuse  = max(dot(diffuse_direction, normal),0.0);

        vec3 spec_direction = reflect(diffuse_direction, normal);
        float specular = pow(max(dot(spec_direction, normalize(position - camera_position)),0.0), shinyness);

        float attenuation = max(1.0 - distance(position, gua_light_information.position[i].xyz)/gua_light_information.color_radius[i].a , 0.0);

        out_color += (tex_color * diffuse + specular) * attenuation * gua_light_information.color_radius[i].rgb;
    }


}
