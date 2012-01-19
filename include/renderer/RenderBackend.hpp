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
/// \brief Declaration of the RenderBackend class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_BACKEND_HPP
#define RENDER_BACKEND_HPP

#include <vector>
#include <string>

#include "renderer/RenderWindow.hpp"
#include "renderer/Geometry.hpp"
#include "renderer/Texture.hpp"
#include "renderer/FrameBufferObject.hpp"

namespace gua {

class CameraNode;
class GeometryNode;
class LightNode;


////////////////////////////////////////////////////////////////////////////////
/// \brief The internal renderer of guacamole.
///
/// It takes a list of meshes, lights and a camera and renders the output to a
/// RenderWindow. Each call of render() will draw an entire new frame.
////////////////////////////////////////////////////////////////////////////////

class RenderBackend {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new RenderBackend. The internal RenderWindow is
        /// initialized by this constructor.
        ///
        /// \param width   The width of the window to be opened.
        /// \param height  The height of the window to be opened,
        /// \param display The display where the window should be placed.
        ////////////////////////////////////////////////////////////////////////
        RenderBackend( int width, int height, std::string const& camera, std::string const& display = ":0.0" );

        ////////////////////////////////////////////////////////////////////////
        /// \brief Renders the given objects.
        ///
        /// When this method is called, all given objects will be rendered to
        /// the associated RenderWindow.
        ///
        /// \param node_list  A list of Meshes to be drawn, with materials and
        ///                   transformations.
        /// \param light_list A list of lights to be drawn.
        /// \param camera     The Camera and it's transformation used for
        ///                   drawing.
        ////////////////////////////////////////////////////////////////////////
        void render( std::vector<GeometryNode*> const& node_list,
                     std::vector<LightNode*> const& light_list,
                     CameraNode* camera );

        std::string const& get_camera_name() const;

    private:
        RenderWindow window_;
        std::string camera_name_;

        Geometry light_sphere_;
        Texture depth_buffer_, color_buffer_, position_buffer_, normal_buffer_;
        FrameBufferObject g_buffer_;
};

}

#endif // RENDER_BACKEND_HPP
