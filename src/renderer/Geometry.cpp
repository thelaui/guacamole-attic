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
/// \brief Definition of the Geometry class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/Geometry.hpp"

// guacamole headers
#include "utils/TextFile.hpp"
#include "utils/debug.hpp"
#include "renderer/LightSphere.hpp"

// external headers
#include <assimp/Importer.hpp>
//#include <assimp/aiPostProcess.h>
//#include <assimp/scene.h>

namespace gua {

Geometry::
Geometry():

    importer_(NULL),
    meshes_() {}

////////////////////////////////////////////////////////////////////////////////

Geometry::
Geometry(std::string const& file_name):

    importer_(NULL),
    meshes_() {

    TextFile file(file_name);

    if (file.is_valid()) {

        importer_ = new Assimp::Importer();
        aiScene const* scene(importer_->ReadFile(file_name,
                                          aiProcessPreset_TargetRealtime_Quality
                                          | aiProcess_CalcTangentSpace ));

        meshes_ = std::vector<Mesh*>(scene->mNumMeshes);

        for (unsigned int n = 0; n < scene->mNumMeshes; ++n)
            meshes_[n] = new Mesh(scene->mMeshes[n]);

    } else {
        WARNING("Failed to load object \"%s\": File does not exist!",
                file_name.c_str());
    }

}

////////////////////////////////////////////////////////////////////////////////

Geometry::
Geometry(char const* buffer_name, unsigned buffer_size):

    importer_(NULL),
    meshes_() {

    importer_ = new Assimp::Importer();
    aiScene const* scene(importer_->ReadFileFromMemory(
                                          buffer_name, buffer_size,
                                          aiProcessPreset_TargetRealtime_Quality
                                          | aiProcess_CalcTangentSpace));

    meshes_ = std::vector<Mesh*>(scene->mNumMeshes);

    for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {
        meshes_[n] = new Mesh(scene->mMeshes[n]);
    }
}

////////////////////////////////////////////////////////////////////////////////

Geometry::
~Geometry() {

    for (auto mesh: meshes_)
        delete mesh;
    if (importer_)
        delete importer_;
}

////////////////////////////////////////////////////////////////////////////////

void Geometry::
draw(RenderContext const& context) const {

    for (auto& mesh: meshes_)
        mesh->draw(context);
}

////////////////////////////////////////////////////////////////////////////////

}
