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

#include "include/renderer/RenderWindow.hpp"

namespace gua {

class SceneGraph;
class Optimizer;
class RenderBackend;

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
        Renderer();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys a Renderer.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Renderer();


		////////////////////////////////////////////////////////////////////////
		///\brief Add a Display.
        ///
        /// Takes a Scenegraph and starts to render.
        ///
        ///\param width   Width of the new display in Pixel.
        ///\param height  Height of the display in Pixel.
        ///\param display    Defines the Xdisplay id that is used to render the scene. Defaults to :0.0 .
        ////////////////////////////////////////////////////////////////////////
        void add_display( int width, int height, std::string const& display = ":0.0");

		////////////////////////////////////////////////////////////////////////
		///\brief Start the Render Loop
        ///
        /// Takes a Scenegraph and starts to render.
        ///
        ///\param scene_graph          The SceneGraph to be processed.
        ////////////////////////////////////////////////////////////////////////
		void start_render_loop( SceneGraph const* scene_graph );

	private:
		std::vector<RenderBackend*> render_backend_list_;
		Optimizer* optimizer_;
};

}

#endif // RENDERER_HPP
