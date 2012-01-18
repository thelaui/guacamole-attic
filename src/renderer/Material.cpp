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
//
/// \file
/// \brief Definition of the Material class.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/Material.hpp"

#include "include/renderer/ShaderProgram.hpp"
#include "include/renderer/RenderContext.hpp"

#include "include/utils/PathParser.hpp"
#include "include/utils/TextFile.hpp"
#include "include/utils/debug.hpp"

namespace gua {

Material::Material():
    texture_(),
    shader_() {}

Material::Material(std::string const& file_name) {
    TextFile file(file_name);

    if (file.is_valid()) {
        construct_from_file(file);
    } else {
        WARNING("Failed to load material description \"%s\": File does not exist!", file_name.c_str());
    }
}

void Material::use(RenderContext const& context) const {
    texture_.bind(context, 0);
    shader_.use(context);
}

Texture const& Material::get_texture() const {
    return texture_;
}

ShaderProgram const& Material::get_shader() const {
    return shader_;
}

void Material::construct_from_file(TextFile const& file) {
    std::string content(file.get_content());
    std::stringstream parse_stream(content);

    std::string current_string;
    std::string texture_string;
    std::string vertex_string;
    std::string fragment_string;

    while (parse_stream >> current_string) {
        if (current_string == "color:") {
            parse_stream >> current_string;
            parse_stream >> current_string;
            parse_stream >> current_string;
        } else if (current_string == "texture:") {
            parse_stream >> texture_string;
        } else if (current_string == "vertex_shader:") {
            parse_stream >> vertex_string;
        } else if (current_string == "fragment_shader:") {
            parse_stream >> fragment_string;
        }
        else WARNING("In \"%s\": \"%s\" is not a valid attribute!",
                     file.get_file_name().c_str(), current_string.c_str());
    }

    PathParser location_parser;
    location_parser.parse(file.get_file_name());

    PathParser path_parser;

    if (texture_string.length() > 0) {
        path_parser.parse(texture_string);
        path_parser.make_absolute(location_parser.get_path(true));
        texture_ = Texture(path_parser.get_path());
    }

    path_parser.parse(vertex_string);
    path_parser.make_absolute(location_parser.get_path(true));

    VertexShader vertex_shader(path_parser.get_path());

    path_parser.parse(fragment_string);
    path_parser.make_absolute(location_parser.get_path(true));

    FragmentShader fragment_shader(path_parser.get_path());

    shader_ = ShaderProgram(vertex_shader, fragment_shader);
}

}
