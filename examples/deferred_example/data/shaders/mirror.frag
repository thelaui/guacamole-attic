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

in vec3 normal;
in vec2 texcoord;
in vec3 position;

uniform sampler2D tex_color;
uniform sampler2D tex_specular;
uniform sampler2D tex_mirror;

layout(location=0) out vec3 out_color;
layout(location=1) out vec3 out_normal;
layout(location=2) out vec3 out_specular;
layout(location=3) out vec3 out_position;

void main() {
    vec2 coord = texcoord*5;

    float spec = texture2D(tex_specular, coord).r;

	out_color    = (1-spec)*texture2D(tex_color, coord).rgb + spec*texture2D(tex_mirror, texcoord).rgb;
    out_specular = vec3(spec, max(max(out_color.r, out_color.g), out_color.b), 0);
	out_normal   = normal;
	out_position = position;
}
