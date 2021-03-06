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
//
/// \file
/// \brief Definition of the MaterialBase class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/MaterialBase.hpp"

// guacamole headers
#include "utils/Directory.hpp"

// external headers
#include <sstream>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

void MaterialBase::
load_materials_from(std::string const& path_to_materials) {

    gua::Directory dir(path_to_materials);
    std::stringstream content(dir.get_content());
    std::string parse_string;

    while (content >> parse_string) {
        unsigned suffix_pos(parse_string.find(".gmd"));

        if(parse_string.length() - suffix_pos == 4) {
            auto mat(new Material(dir.get_directory_name() + parse_string));

            instance()->add(parse_string.substr(0, suffix_pos),
                            std::shared_ptr<Material>(mat));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

}


