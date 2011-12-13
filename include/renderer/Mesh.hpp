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
/// \brief Declaration of the Mesh class.
////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

class aiMesh;
class RenderContext;

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores geometry data.
///
/// A mesh can be loaded from a Assimp mesh and the draw onto multiple contexts.
/// Do not use this class directly, it is just used by the Geometry class to
/// store the individual meshes of a file.
////////////////////////////////////////////////////////////////////////////////

class Mesh {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new and empty Mesh.
        ////////////////////////////////////////////////////////////////////////
        Mesh();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from an Assimp mesh.
        ///
        /// Initializes the mesh from a given Assimp mesh.
        ///
        /// \param mesh The Assimp mesh to load the data from.
        ////////////////////////////////////////////////////////////////////////
        Mesh( aiMesh* mesh );

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Cleans up and frees all associated memory.
        ////////////////////////////////////////////////////////////////////////
        ~Mesh();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Draws the Mesh.
        ///
        /// Draws the Mesh to the given context.
        ///
        /// \param context The RenderContext to draw onto.
        ////////////////////////////////////////////////////////////////////////
        void draw(RenderContext const& context) const;

    private:
        void upload_to(RenderContext const& context) const;

        mutable std::vector<unsigned> vaos_;
        aiMesh* mesh_;
};

#endif // MESH_HPP


