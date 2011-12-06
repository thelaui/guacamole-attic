#include "include/renderer/Geometry.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/utils/fileUtils.hpp"
#include "include/utils/debug.hpp"

Geometry::Geometry():
    meshes_() {}

Geometry::Geometry(std::string const& file):
    meshes_() {

    if (fileUtils::file_exists(file)) {
        Assimp::Importer* importer = new Assimp::Importer();
        aiScene const* scene = importer->ReadFile( file, aiProcessPreset_TargetRealtime_Quality);

        meshes_ = std::vector<Mesh>(scene->mNumMeshes);

        for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {
            meshes_[n] = Mesh(scene->mMeshes[n]);
        }
    }
}

Geometry::~Geometry() {

}

void Geometry::draw() const {

}
