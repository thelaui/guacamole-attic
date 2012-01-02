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

in vec3 normal;

out vec4 out_color;

void main() {
	vec3 lightDirTop  = normalize(vec3(1.0,2.0,5.0));
	vec3 lightDirBack = normalize(vec3(0.0, 10.0,-10.0));
	vec3 lightDirFill = normalize(vec3(-10.0,-5.0,1.0));

	vec3 top  = vec3(0.6, 0.6, 1.0);
	vec3 back = vec3(1.0, 1.0, 1.0);
	vec3 fill = vec3(0.8, 0.6, 0.3);

	float intensityTop  = pow(max(dot(lightDirTop,normal),0.0), 3.0);
	float intensityBack = max(dot(lightDirBack,normal),0.0);
	float intensityFill = max(dot(lightDirFill,normal),0.0);

	float fakeSpec = pow(max(dot(lightDirTop,normal),0.0), 50.0);

	vec3 amb = vec3(0.1, 0.1, 0.1);

	out_color = vec4(intensityTop*top + intensityBack*back + intensityFill*fill + amb + fakeSpec, 1.0);
}
