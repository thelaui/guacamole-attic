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
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the CameraCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDERER_SERVER_HPP
#define GUA_RENDERER_HPP

#include <vector>
#include <string>
#include <thread>

namespace gua {

class SceneGraph;
class RenderClient;
class RenderPipeline;

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to provide a renderer frontend interface to the user.
///
////////////////////////////////////////////////////////////////////////////////
class RenderServer {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a new RenderServer.
        ///
        ////////////////////////////////////////////////////////////////////////
        RenderServer(std::vector<RenderPipeline*> const& pipelines);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys a RenderServer.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~RenderServer();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Start the Render Loop
        ///
        /// Takes a Scenegraph and starts to render.
        ///
        ///\param scene_graph          The SceneGraph to be processed.
        ////////////////////////////////////////////////////////////////////////
        void queue_draw( SceneGraph const* scene_graph );

    private:
        std::vector<RenderClient*> render_clients_;
};

}

#endif // GUA_RENDERER_SERVER_HPP
