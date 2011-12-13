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
/// \brief Definition of the Mesh class.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/Mesh.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "include/renderer/RenderContext.hpp"
#include "include/renderer/ShaderProgram.hpp"
#include "include/utils/debug.hpp"

Mesh::Mesh():
    vaos_(),
    mesh_(NULL) {}

Mesh::Mesh( aiMesh* mesh ):
    vaos_(),
    mesh_(mesh) {}

Mesh::~Mesh() {
    for (auto vao: vaos_)
        if (vao)
            glDeleteVertexArrays(1, &vao);
}

void Mesh::upload_to(RenderContext const& context) const {
    std::vector<unsigned> face_array(mesh_->mNumFaces * 3);

    for (unsigned t = 0; t < mesh_->mNumFaces; ++t) {
        const struct aiFace* face = &mesh_->mFaces[t];

        face_array[t*3]   = face->mIndices[0];
        face_array[t*3+1] = face->mIndices[1];
        face_array[t*3+2] = face->mIndices[2];
    }

     // generate Vertex Array for mesh
    unsigned vao(0);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    if (vaos_.size() <= context.id) {
        vaos_.resize(context.id+1);
    }

    vaos_[context.id] = vao;

    // buffer for faces
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * mesh_->mNumFaces * 3, &(*face_array.begin()), GL_STATIC_DRAW);

    // buffer for vertex positions
    if (mesh_->HasPositions()) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh_->mNumVertices, mesh_->mVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(ShaderProgram::vertex_location);
        glVertexAttribPointer(ShaderProgram::vertex_location, 3, GL_FLOAT, 0, 0, 0);
    }

    // buffer for vertex normals
    if (mesh_->HasNormals()) {
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh_->mNumVertices, mesh_->mNormals, GL_STATIC_DRAW);
        glEnableVertexAttribArray(ShaderProgram::normal_location);
        glVertexAttribPointer(ShaderProgram::normal_location, 3, GL_FLOAT, 0, 0, 0);
    }

    // unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void Mesh::draw(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (vaos_.size() <= context.id || vaos_[context.id] == 0) {
        upload_to(context);
    }

    // bind the geometry and draw it
    glBindVertexArray(vaos_[context.id]);
    glDrawElements(GL_TRIANGLES, mesh_->mNumFaces*3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



