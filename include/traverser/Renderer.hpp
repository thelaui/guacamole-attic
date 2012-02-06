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
/// \brief Declaration of the CameraCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <string>
#include <thread>

#include "renderer/RenderWindow.hpp"

namespace gua {

class SceneGraph;
class Optimizer;
class RenderClient;

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to provide a renderer frontend interface to the user.
///
////////////////////////////////////////////////////////////////////////////////

class Renderer {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a new Renderer.
        ///
        ////////////////////////////////////////////////////////////////////////
        Renderer(std::vector<std::vector<std::string>> const& windows);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys a Renderer.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Renderer();

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
        Optimizer* optimizer_;
};

}

#endif // RENDERER_HPP
