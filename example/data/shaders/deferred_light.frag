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

#version 330

in vec3 position;
in vec3 normal;
in vec3 light_position_camera_space;
in float light_radius;

out vec4 out_color;

uniform vec3      light_color;
uniform sampler2D color_buffer;
uniform sampler2D position_buffer;
uniform sampler2D normal_buffer;
uniform float     texel_width;
uniform float     texel_height;



void main(void)
{
  /// texcoord for coresponding fragment on the screen
  vec2 screen_tex_coords = vec2(gl_FragCoord.s*texel_width,
                               gl_FragCoord.t*texel_height);

  // read from the G-Buffer
  vec4 fragment_color = vec4(texture2D( color_buffer, screen_tex_coords).rgb, 1.0);
  vec3 fragment_position = texture2D( position_buffer, screen_tex_coords).rgb;
  vec3 fragment_normal = texture2D( normal_buffer, screen_tex_coords).rgb;

    fragment_color = vec4(0.5, 0.5, 0.5, 1.0);

  // discards all fragments outside the light radius

  vec3  fragment_to_light = light_position_camera_space - fragment_position;

  if ( length(fragment_to_light) > light_radius)
  {
    discard;
  }


  // discard all fragments that are facing away from the light ( use the dot product of two vectors )

  vec3 fragment_to_light_direction = normalize(fragment_to_light);

  if ( dot(fragment_normal, fragment_to_light_direction) < 0)
  {
    discard;
  }



  // PHONG ////////////////////////////////////////////////////////////////////
  // diffuse part
  vec4 diffuse_color = vec4(light_color, 1.f) * dot(fragment_normal, fragment_to_light_direction);

  // specular part
  vec3  reflection_dir = normalize( reflect(-fragment_to_light_direction, fragment_normal));
  float specular = max(0, pow(dot(reflection_dir, -normalize(fragment_position)), 100));

  // the intensity of the lights reduces with the distance to it
  float attenuation = (1.0 - (length(fragment_to_light) / (light_radius)));

  out_color = fragment_color * attenuation * diffuse_color + vec4(light_color, 1.f) * specular * attenuation;
}




