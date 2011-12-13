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

#include "include/renderer/RenderWindow.hpp"

class CameraNode;
class GeometryNode;
class LightNode;

////////////////////////////////////////////////////////////////////////////////
/// \brief The internal renderer of guacamole.
///
/// It takes a list of meshes, lights and a camera and renders the output to a
/// RenderWindow.
////////////////////////////////////////////////////////////////////////////////

class RenderBackend {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param width
        /// \param height
        /// \param display
        ////////////////////////////////////////////////////////////////////////
        RenderBackend( int width, int height, std::string const& display = ":0.0" );

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param node_list
        /// \param light_list
        /// \param camera
        ////////////////////////////////////////////////////////////////////////
        void render( std::vector<GeometryNode*> const& node_list,
                     std::vector<LightNode*> const& light_list,
                     CameraNode* camera );

    private:
        RenderWindow window_;
};

#endif // RENDER_BACKEND_HPP
