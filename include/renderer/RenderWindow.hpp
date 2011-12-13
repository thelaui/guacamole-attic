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
/// \brief Declaration of the FragmentShader class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <memory>
#include <string>

#include "include/renderer/RenderContext.hpp"

class Geometry;

////////////////////////////////////////////////////////////////////////////////
/// \brief
///
///
////////////////////////////////////////////////////////////////////////////////

class RenderWindow {
    public:
        RenderWindow( int width, int height, std::string const& display ) throw (std::string);
        virtual ~RenderWindow();

        void set_active() const;

        void start_frame() const;
        void finish_frame() const;

        void draw(std::shared_ptr<Geometry> geometry) const;

        RenderContext const& get_context() const;

        static void init();

    private:
        static unsigned last_context_id_;

        RenderContext ctx_;

        int frames_;
        int frame_count_;
        long frames_start_;
};

#endif //RENDERWINDOW_HPP
