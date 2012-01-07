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
/// \brief Declaration of the MaterialBase class.
////////////////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_BASE_HPP
#define MATERIAL_BASE_HPP

#include "utils/Singleton.hpp"
#include "renderer/DataBase.hpp"
#include "renderer/Material.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief A data base for materials.
///
/// This DataBase stores material data. It can be accessed via string
/// identifiers.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class MaterialBase: public DataBase<Material>, public Singleton<MaterialBase> {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Pre-loads some Materials.
        ///
        /// This method loads some default materials to the data base.
        ////////////////////////////////////////////////////////////////////////
        static void load_materials_from(std::string const& path_to_materials);

        friend class Singleton<MaterialBase>;

    private:
        MaterialBase() {};
        ~MaterialBase() {};
};

}

#endif // MATERIAL_BASE_HPP
