#include "include/renderer/Mesh.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/utils/debug.hpp"

Mesh::Mesh():
    mesh_(NULL) {}

Mesh::Mesh(std::string const& file):
    mesh_(NULL) {

}

Mesh::~Mesh() {

}

void Mesh::draw() const {

}
