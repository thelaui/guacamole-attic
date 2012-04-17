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

#include "renderer/Geometry.hpp"

#include "renderer/RenderContext.hpp"
#include "renderer/ShaderProgram.hpp"
#include "utils/debug.hpp"
#include "utils/TextFile.hpp"

namespace gua {

Geometry::Geometry():
    meshes_(),
    upload_mutex_(),
    file_name_("") {}

Geometry::Geometry(std::string const& file_name):
    meshes_(),
    upload_mutex_(),
    file_name_(file_name) {}

void Geometry::upload_to(RenderContext const& context) const {

    std::unique_lock<std::mutex> lock(upload_mutex_);

    TextFile tmp(file_name_);
    if (tmp.is_valid()) {
        if (meshes_.size() <= context.id) {
            meshes_.resize(context.id+1);
        }

        meshes_[context.id] = scm::gl::wavefront_obj_geometry_ptr(
            new scm::gl::wavefront_obj_geometry(context.render_device, file_name_));
    }
}

void Geometry::draw(RenderContext const& context) const {
    // upload to GPU if neccessary
    if (meshes_.size() <= context.id || meshes_[context.id] == 0) {
        upload_to(context);
    }

    if (meshes_[context.id])
        meshes_[context.id]->draw_raw(context.render_context);
}

}

