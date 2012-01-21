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
/// \brief Definition of the Geometry class.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/Geometry.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/utils/TextFile.hpp"
#include "include/utils/debug.hpp"

#include "renderer/LightSphere.hpp"


namespace gua {

Geometry::Geometry():
    meshes_() {}

Geometry::Geometry(std::string const& file_name):
    meshes_() {

    TextFile file(file_name);

    if (file.is_valid()) {
        Assimp::Importer* importer = new Assimp::Importer();
        aiScene const* scene = importer->ReadFile(file_name, aiProcessPreset_TargetRealtime_Quality);

        meshes_ = std::vector<Mesh>(scene->mNumMeshes);

        for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {
            meshes_[n] = Mesh(scene->mMeshes[n]);
        }
    } else {
        WARNING("Failed to load object \"%s\": File does not exist!", file_name.c_str());
    }

}

Geometry::Geometry(char const* buffer_name, unsigned buffer_size):
    meshes_() {
    Assimp::Importer* importer = new Assimp::Importer();
    aiScene const* scene = importer->ReadFileFromMemory(buffer_name, buffer_size, aiProcessPreset_TargetRealtime_Quality);

    meshes_ = std::vector<Mesh>(scene->mNumMeshes);

    for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {
        meshes_[n] = Mesh(scene->mMeshes[n]);
    }
}

void Geometry::draw(RenderContext const& context) const {
    for (auto& mesh: meshes_)
        mesh.draw(context);
}

}
