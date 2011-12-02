#include "include/renderer/Mesh.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/utils/debug.hpp"

Mesh::Mesh():
    vaos_(),
    numFaces(0),
    aMesh_(NULL) {}

Mesh::Mesh(aiMesh* aMesh):
    vaos_(),
    numFaces(0),
    aMesh_(aMesh) {}

Mesh::~Mesh() {
    for (auto vao = vaos_.begin(); vao != vaos_.end(); ++vao)
        glDeleteVertexArrays(1,vao->second);
}

void Mesh::upload(int id) {
    numFaces = aMesh_->mNumFaces;
    std::vector<unsigned int> faceArray(numFaces * 3);

    faceArray[0] = 7;

    for (unsigned int t = 0; t < numFaces; ++t) {
        const struct aiFace* face = &aMesh_->mFaces[t];

        faceArray[t*3]   = face->mIndices[0];
        faceArray[t*3+1] = face->mIndices[1];
        faceArray[t*3+2] = face->mIndices[2];
    }

     // generate Vertex Array for aMesh
    GLuint* vao = new GLuint();
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    vaos_.insert(std::make_pair(id, vao));

    // buffer for faces
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numFaces * 3, &(*faceArray.begin()), GL_STATIC_DRAW);

    // buffer for vertex positions
    if (aMesh_->HasPositions()) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*aMesh_->mNumVertices, aMesh_->mVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(Drawer::vertexLoc);
        glVertexAttribPointer(Drawer::vertexLoc, 3, GL_FLOAT, 0, 0, 0);
    }

    // buffer for vertex normals
    if (aMesh_->HasNormals()) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*aMesh_->mNumVertices, aMesh_->mNormals, GL_STATIC_DRAW);
        glEnableVertexAttribArray(Drawer::normalLoc);
        glVertexAttribPointer(Drawer::normalLoc, 3, GL_FLOAT, 0, 0, 0);
    }

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

GLuint* Mesh::vao(int id) {
    return vaos_[id];
}
