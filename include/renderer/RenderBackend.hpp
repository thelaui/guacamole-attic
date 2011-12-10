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
/// \brief Declaration of the internal renderer.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_BACKEND_HPP
#define RENDER_BACKEND_HPP

#include <vector>
#include <string>

class Camera;
class Geometry;
class Light;

class RenderBackend {
    public:
        RenderBackend( int width, int height, std::string const& display = ":0.0" );
        virtual ~RenderBackend();

        void render( std::vector<Geometry*> const& node_list,
                     std::vector<Light*> const& light_list,
                     Camera const& camera );

    private:

};

#endif // RENDER_BACKEND_HPP
