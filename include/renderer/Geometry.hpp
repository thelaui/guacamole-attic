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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the Geometry class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_GEOMETRY_HPP
#define GUA_GEOMETRY_HPP

#include <string>
#include <vector>

#include "renderer/Mesh.hpp"

namespace Assimp {
    class Importer;
}

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Loads and draws meshes.
///
/// This class can load mesh data from files and display them in multiple
/// contexts. A Geometry object is made of several Mesh objects.
////////////////////////////////////////////////////////////////////////////////
class Geometry {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Constructs a new and empty Geometry.
        ////////////////////////////////////////////////////////////////////////
        Geometry();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from a file.
        ///
        /// Creates a new Geometry from a given file.
        ///
        /// \param file_name The file to load the meh's data from.
        ////////////////////////////////////////////////////////////////////////
        Geometry(std::string const& file_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        ~Geometry();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from memory buffer.
        ///
        /// Creates a new Geometry from a existing memory buffer.
        ///
        /// \param buffer_name The buffer to load the meh's data from.
        /// \param buffer_size The buffer's size.
        ////////////////////////////////////////////////////////////////////////
        Geometry(char const* buffer_name, unsigned buffer_size);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Draws the Geometry.
        ///
        /// Draws this Geometry object to the given context.
        ///
        /// \param context The RenderContext to which this object should be
        /// drawn.
        ////////////////////////////////////////////////////////////////////////
        void draw(RenderContext const& context) const;

    private:
        Assimp::Importer* importer_;
        std::vector<Mesh*> meshes_;
};

}

#endif // GUA_GEOMETRY_HPP
