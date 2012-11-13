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

in vec2 out_texcoord;
in vec3 out_camera_position;

uniform sampler2D in_color;
uniform sampler2D in_depth_stencil;

layout(location=0) out vec3 color;

void main() {
    float fog = min(1, max (0, texture2D(in_depth_stencil, out_texcoord).x * 3.0 - 2.5));
    float vignette = length(out_texcoord - 0.5);
    color = (texture2D(in_color, out_texcoord).rgb + 0.4 * fog) + vignette * vignette;

//    const float vblurSize = 1.0/512.0;
//    vec4 sum = vec4(0.0);
//
//    // blur in y (vertical)
//    // take nine samples, with the distance blurSize between them
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y - 4.0*vblurSize)) * 0.05;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y - 3.0*vblurSize)) * 0.09;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y - 2.0*vblurSize)) * 0.12;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y - vblurSize)) * 0.15;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y)) * 0.16;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y + vblurSize)) * 0.15;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y + 2.0*vblurSize)) * 0.12;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y + 3.0*vblurSize)) * 0.09;
//    sum += texture2D(RTBlurH, vec2(out_texcoord.x, out_texcoord.y + 4.0*vblurSize)) * 0.05;
}
