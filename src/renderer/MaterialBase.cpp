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
/// \brief Definition of the MaterialBase class.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/MaterialBase.hpp"

#include "include/utils/Directory.hpp"

#include <sstream>

namespace gua {

void MaterialBase::load_material_from(std::string const& path_to_materials) {
//    ShaderProgram shiny(VertexShader("data/shaders/shiny.vert"), FragmentShader("data/shaders/shiny.frag"));
//    instance()->add("shiny", std::shared_ptr<Material>(new Material(shiny)));
//
//    ShaderProgram matt(VertexShader("data/shaders/matt.vert"), FragmentShader("data/shaders/matt.frag"));
//    instance()->add("matt", std::shared_ptr<Material>(new Material(matt)));

    gua::Directory directory(path_to_materials);

    std::stringstream content(directory.get_content());

    std::string parse_string;
    while (content >> parse_string) {
        unsigned suffix_pos(parse_string.find(".gmd"));
        if(suffix_pos != std::string::npos) {
            instance()->add(parse_string.substr(0, suffix_pos),
                            std::shared_ptr<Material>(new Material(path_to_materials + parse_string)));
        }
    }
}

}


