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

#include "renderer/Mesh.hpp"

#include <assimp/assimp.hpp>
#include <assimp/aiPostProcess.h>
#include <assimp/aiScene.h>

#include "renderer/RenderContext.hpp"
#include "renderer/ShaderProgram.hpp"
#include "utils/debug.hpp"

namespace {
    struct Vertex {
        scm::math::vec3f pos;
        scm::math::vec2f tex;
        scm::math::vec3f normal;
        scm::math::vec3f tangent;
        scm::math::vec3f bitangent;
    };
}

namespace gua {

Mesh::Mesh():
    vertices_(),
    indices_(),
    vertex_array_(),
    upload_mutex_(),
    mesh_(NULL) {}

Mesh::Mesh( aiMesh* mesh ):
    vertices_(),
    indices_(),
    vertex_array_(),
    upload_mutex_(),
    mesh_(mesh) {}

Mesh::~Mesh() {

}

void Mesh::upload_to(RenderContext const& context) const {
    if (!mesh_->HasPositions()) {
        WARNING("Unable to load Mesh! Has no vertex data.");
        return;
    }

    std::unique_lock<std::mutex> lock(upload_mutex_);

    if (vertices_.size() <= context.id) {
        vertices_.resize(context.id+1);
        indices_.resize(context.id+1);
        vertex_array_.resize(context.id+1);
    }

    vertices_[context.id] = context.render_device->create_buffer(scm::gl::BIND_VERTEX_BUFFER, scm::gl::USAGE_STATIC_DRAW, mesh_->mNumVertices * sizeof(Vertex), 0);

    Vertex* data = static_cast<Vertex*>(context.render_context->map_buffer(vertices_[context.id], scm::gl::ACCESS_WRITE_INVALIDATE_BUFFER));

    for (unsigned v(0); v < mesh_->mNumVertices; ++v) {
        data[v].pos = scm::math::vec3(mesh_->mVertices[v].x,
                                      mesh_->mVertices[v].y,
                                      mesh_->mVertices[v].z);

        if (mesh_->HasTextureCoords(0)) {
            data[v].tex = scm::math::vec2(mesh_->mTextureCoords[0][v].x,
                                          mesh_->mTextureCoords[0][v].y);
        } else {
            data[v].tex = scm::math::vec2(0.f, 0.f);
        }

        if (mesh_->HasNormals()) {
            data[v].normal = scm::math::vec3(mesh_->mNormals[v].x,
                                             mesh_->mNormals[v].y,
                                             mesh_->mNormals[v].z);
        } else {
            data[v].normal = scm::math::vec3(0.f, 0.f, 0.f);
        }

        if (mesh_->HasTangentsAndBitangents()) {
            data[v].tangent = scm::math::vec3(mesh_->mTangents[v].x,
                                              mesh_->mTangents[v].y,
                                              mesh_->mTangents[v].z);
            data[v].bitangent = scm::math::vec3(mesh_->mBitangents[v].x,
                                              mesh_->mBitangents[v].y,
                                              mesh_->mBitangents[v].z);
        } else {
            data[v].tangent = scm::math::vec3(0.f, 0.f, 0.f);
            data[v].bitangent = scm::math::vec3(0.f, 0.f, 0.f);
        }
    }

    context.render_context->unmap_buffer(vertices_[context.id]);

    std::vector<unsigned> index_array(mesh_->mNumFaces * 3);

    for (unsigned t = 0; t < mesh_->mNumFaces; ++t) {
        const struct aiFace* face = &mesh_->mFaces[t];

        index_array[t*3]   = face->mIndices[0];
        index_array[t*3+1] = face->mIndices[1];
        index_array[t*3+2] = face->mIndices[2];
    }

    indices_[context.id] = context.render_device->create_buffer(scm::gl::BIND_INDEX_BUFFER, scm::gl::USAGE_STATIC_DRAW,
                                                                mesh_->mNumFaces * 3 * sizeof(unsigned), &index_array[0]);

    vertex_array_[context.id] = context.render_device->create_vertex_array(scm::gl::vertex_format(0, 0, scm::gl::TYPE_VEC3F, sizeof(Vertex))
                                                                                        (0, 1, scm::gl::TYPE_VEC2F, sizeof(Vertex))
                                                                                        (0, 2, scm::gl::TYPE_VEC3F, sizeof(Vertex))
                                                                                        (0, 3, scm::gl::TYPE_VEC3F, sizeof(Vertex))
                                                                                        (0, 4, scm::gl::TYPE_VEC3F, sizeof(Vertex)),
                                                                                        {vertices_[context.id]});

}

void Mesh::draw(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (vertices_.size() <= context.id || vertices_[context.id] == NULL) {
        upload_to(context);
    }

    scm::gl::context_vertex_input_guard vig(context.render_context);

    context.render_context->bind_vertex_array(vertex_array_[context.id]);

    context.render_context->bind_index_buffer(indices_[context.id], scm::gl::PRIMITIVE_TRIANGLE_LIST, scm::gl::TYPE_UINT);

    context.render_context->apply();
    context.render_context->draw_elements(mesh_->mNumFaces*3);
}

}

