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
/// \brief Declaration of the TextureBase class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_TEXTURE_BASE_HPP
#define GUA_TEXTURE_BASE_HPP

#include "utils/Singleton.hpp"
#include "renderer/DataBase.hpp"
#include "renderer/Texture.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief A data base for textures.
///
/// This DataBase stores texture data. It can be accessed via string
/// identifiers.
////////////////////////////////////////////////////////////////////////////////

class TextureBase: public DataBase<Texture>, public Singleton<TextureBase> {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) shader program.
        ////////////////////////////////////////////////////////////////////////
        static void load_textures_from(std::string const& path_to_textures);

        friend class Singleton<TextureBase>;

    private:
        TextureBase() {};
        ~TextureBase() {};
};

}

#endif // GUA_TEXTURE_BASE_HPP



