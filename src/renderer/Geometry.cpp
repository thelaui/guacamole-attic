#include "include/renderer/Geometry.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/utils/TextFile.hpp"
#include "include/utils/debug.hpp"

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

Geometry::~Geometry() {

}

void Geometry::draw(RenderContext const& context) const {
    for (auto& mesh: meshes_)
        mesh.draw(context);
}
