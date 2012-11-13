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

in vec3 out_camera_position;
in vec2 out_texcoord;

uniform sampler2D tiles_tex;
uniform sampler2D tiles_small_tex;
uniform sampler2D wood_tex;

uniform sampler2D in_normal;
uniform sampler2D in_tex_coords_mat_id;
uniform sampler2D in_depth_stencil;
uniform sampler2D in_diffuse;
uniform sampler2D in_specular;

layout(location=0) out vec3 color;

void main() {
    int mat_id = int(texture2D(in_tex_coords_mat_id, out_texcoord).z);
    vec2 texcoords = texture2D(in_tex_coords_mat_id, out_texcoord).xy;
    vec3 diffuse = texture2D(in_diffuse, out_texcoord).rgb;
    vec3 specular = texture2D(in_specular, out_texcoord).rgb;

    if (mat_id == 1)
        color = texture2D(tiles_small_tex, texcoords).rgb * diffuse + specular;

    else if (mat_id == 2)
        color = texture2D(wood_tex, texcoords).rgb * diffuse + specular;

    else if (mat_id == 3)
        color = texture2D(tiles_tex, texcoords).rgb * diffuse + specular;

    else if (mat_id == 4)
        color = vec3(1,1,1);

    else
        color = vec3(0, 0, 0);

   // color = vec3(texcoords, 0.0);
}
