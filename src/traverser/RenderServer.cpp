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
/// \brief Definition of the RenderServer class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "traverser/RenderServer.hpp"

// guacamole headers
#include "scenegraph/SceneGraph.hpp"
#include "traverser/RenderClient.hpp"
#include "traverser/Optimizer.hpp"
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

RenderServer::
RenderServer(std::vector<RenderPipeline*> const& pipelines) {

    for (auto& pipeline: pipelines)
        render_clients_.push_back(new RenderClient(pipeline));
}

////////////////////////////////////////////////////////////////////////////////

RenderServer::
~RenderServer(){

    for (auto c(render_clients_.begin()); c != render_clients_.end(); ++c){
        delete (*c);
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderServer::
queue_draw( SceneGraph const* scene_graph ) {

    for (auto c(render_clients_.begin()); c != render_clients_.end(); ++c) {
        (*c)->queue_draw(scene_graph);
    }
}

////////////////////////////////////////////////////////////////////////////////

}
