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

#extension GL_ARB_shading_language_include : require

#include </gua/LightInformation.glslh>

in vec3 position;

layout(location=0) out vec3 out_color;

void main() {
    out_color = vec3(0, 0, 0);
    float closest = -1;

    for(int i=0; i<gua_light_information.light_count.x; ++i) {
        float dist = distance(position, gua_light_information.position[i].xyz);
        if (dist < closest || closest < 0) {
            closest = dist;
            out_color = gua_light_information.color_radius[i].rgb;
        }
    }
}
