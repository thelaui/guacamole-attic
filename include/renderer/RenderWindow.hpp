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
/// \brief Declaration of the RenderWindow class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERWINDOW_HPP
#define RENDERWINDOW_HPP

#include <memory>
#include <string>

#include "include/renderer/RenderContext.hpp"

namespace gua {

class Geometry;

////////////////////////////////////////////////////////////////////////////////
/// \brief A window for displaying stuff.
///
/// It's an X window which can display OpenGL stuff.
////////////////////////////////////////////////////////////////////////////////

class RenderWindow {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new RenderWindow. It owns a RenderContext where Geomtries
        /// can be drawn to.
        ///
        /// \param width   The width of the window.
        /// \param height  The height of the window.
        /// \param display The display where this window should be opened.
        /// \throw An error message.
        ////////////////////////////////////////////////////////////////////////
        RenderWindow( int width, int height, std::string const& display ) throw (std::string);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Cleans all associated memory.
        ////////////////////////////////////////////////////////////////////////
        virtual ~RenderWindow();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Activate the context of this window.
        ///
        /// Makes the RenderContext of this window current. All preceeding
        /// OpenGL calls will be invoked on this window.
        ////////////////////////////////////////////////////////////////////////
        void set_active() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Starts the drawing of a new frame.
        ///
        /// This should be called when a new frame is about to be drawn.
        ////////////////////////////////////////////////////////////////////////
        void start_frame() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Ends the drawing of a new frame.
        ///
        /// This should be called when drawing a frame has been done.
        ////////////////////////////////////////////////////////////////////////
        void finish_frame() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Draws the given Geometry.
        ///
        /// The given Geometry is drawn to the window.
        ///
        /// \param geometry The Geometry to be drawn.
        ////////////////////////////////////////////////////////////////////////
        void draw(std::shared_ptr<Geometry> const& geometry) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Get the RenderContext of this window.
        ///
        /// Can be called in order to retrieve the RenderContext of this
        /// RenderWindow.
        ///
        /// \return The context owned by this window.
        ////////////////////////////////////////////////////////////////////////
        RenderContext const& get_context() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Initialize RenderWindows.
        ///
        /// This should be called once in every application using guacamole.
        ////////////////////////////////////////////////////////////////////////
        static void init();

    private:
        static unsigned last_context_id_;

        RenderContext ctx_;

        int frames_;
        int frame_count_;
        long frames_start_;
};

}

#endif //RENDERWINDOW_HPP
