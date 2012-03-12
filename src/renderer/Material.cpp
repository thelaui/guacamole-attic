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

#include "renderer/Material.hpp"

#include "renderer/ShaderProgram.hpp"
#include "renderer/RenderContext.hpp"
#include "renderer/TextureBase.hpp"

#include "utils/PathParser.hpp"
#include "utils/TextFile.hpp"
#include "utils/debug.hpp"

namespace gua {

Material::Material():
    texture_uniforms_(),
    float_uniforms_(),
    shader_() {}

Material::Material(std::string const& file_name):
    texture_uniforms_(),
    float_uniforms_() {

    TextFile file(file_name);

    if (file.is_valid()) {
        construct_from_file(file);
    } else {
        WARNING("Failed to load material description \"%s\": File does not exist!", file_name.c_str());
    }
}

Material::~Material() {}

void Material::use(RenderContext const& context) const {
    shader_.use(context);

    for (auto val : float_uniforms_)
        shader_.set_float(context, val.first, val.second);

    for (auto val : texture_uniforms_)
        shader_.set_sampler2D(context, val.first, *val.second);
}

void Material::unuse(RenderContext const& context) const {
    shader_.unuse();
}

void Material::set_uniform_float(std::string const& uniform_name, float value) {
    float_uniforms_[uniform_name] = value;
}

void Material::set_uniform_texture(std::string const& uniform_name, std::shared_ptr<Texture> const& value) {
    texture_uniforms_[uniform_name] = value;
}

void Material::set_uniform_texture(std::string const& uniform_name, std::string const& texture_name) {
    auto searched_tex(TextureBase::instance()->get(texture_name));
    if (searched_tex)
        texture_uniforms_[uniform_name] = searched_tex;
    else WARNING ("A texture with the name %s does not exist within the database!", texture_name.c_str());
}

ShaderProgram const& Material::get_shader() const {
    return shader_;
}

void Material::construct_from_file(TextFile const& file) {
    std::string content(file.get_content());
    std::stringstream parse_stream(content);

    std::string current_string;
    std::string vertex_string;
    std::string fragment_string;

    while (parse_stream >> current_string) {
        if (current_string == "texture") {
            parse_stream >> current_string;
            std::string texture_name;
            parse_stream >> texture_name;
            set_uniform_texture(current_string, texture_name);
        } else if (current_string == "float") {
            parse_stream >> current_string;
            float value;
            parse_stream >> value;
            set_uniform_float(current_string, value);
        } else if (current_string == "vertex_shader") {
            parse_stream >> vertex_string;
        } else if (current_string == "fragment_shader") {
            parse_stream >> fragment_string;
        }
        else WARNING("In \"%s\": \"%s\" is not a valid attribute!",
                     file.get_file_name().c_str(), current_string.c_str());
    }

    PathParser location_parser;
    location_parser.parse(file.get_file_name());

    PathParser path_parser;

    path_parser.parse(vertex_string);
    path_parser.make_absolute(location_parser.get_path(true));

    VertexShader vertex_shader(path_parser.get_path());

    path_parser.parse(fragment_string);
    path_parser.make_absolute(location_parser.get_path(true));

    FragmentShader fragment_shader(path_parser.get_path());

    shader_ = ShaderProgram(vertex_shader, fragment_shader);
}

}
