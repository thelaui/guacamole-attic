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

#include <scm/gl_util/primitives/quad.h>

#include "renderer/RenderContext.hpp"
#include "renderer/ShaderProgram.hpp"
#include "renderer/enums.hpp"

namespace gua {

class Geometry;
class Texture;

////////////////////////////////////////////////////////////////////////////////
/// \brief A window for displaying stuff.
///
/// It's an X window which can display OpenGL stuff.
////////////////////////////////////////////////////////////////////////////////

class RenderWindow {
    public:

        struct Description {
            Description(int w, int h, std::string const& titl, std::string const& disp, StereoMode str_md = MONO):
                width(w),
                height(h),
                title(titl),
                display(disp),
                stereo_mode(str_md) {}

            int width, height;
            std::string title, display;
            StereoMode stereo_mode;
        };

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new RenderWindow. It owns a RenderContext where Geomtries
        /// can be drawn to.
        ///
        /// \param width   The width of the window.
        /// \param height  The height of the window.
        /// \param window_title The window's title.
        /// \param display The display where this window should be opened.
        /// \throw An error message.
        ////////////////////////////////////////////////////////////////////////
        RenderWindow( Description const& description ) throw (std::string);

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
        void set_active(bool active) const;

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
        /// \brief Draws the given Texture to the window.
        ///
        /// The given Texture is drawn to the window.
        ///
        /// \param texture The Texture to be drawn.
        ////////////////////////////////////////////////////////////////////////
        void display_mono(std::shared_ptr<Texture> const& texture);
        void display_stereo(std::shared_ptr<Texture> const& left_texture,
                            std::shared_ptr<Texture> const& right_texture,
                            StereoMode stereo_mode);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Get the RenderContext of this window.
        ///
        /// Can be called in order to retrieve the RenderContext of this
        /// RenderWindow.
        ///
        /// \return The context owned by this window.
        ////////////////////////////////////////////////////////////////////////
        RenderContext const& get_context() const;

    private:
        static unsigned last_context_id_;

        RenderContext ctx_;

        ShaderProgram fullscreen_shader_;
        scm::gl::quad_geometry_ptr fullscreen_quad_;

        int frames_;
        int frame_count_;
        long frames_start_;

        scm::gl::depth_stencil_state_ptr depth_stencil_state_;
};

}

#endif //RENDERWINDOW_HPP
