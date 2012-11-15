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
/// \brief Declaration of the RenderWindow class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDERWINDOW_HPP
#define GUA_RENDERWINDOW_HPP

// guacamole headers
#include "renderer/RenderContext.hpp"
#include "renderer/ShaderProgram.hpp"
#include "renderer/WarpMatrix.hpp"
#include "renderer/enums.hpp"

// external headers
#include <memory>
#include <string>
#include <scm/gl_util/primitives/quad.h>

namespace gua {

class Geometry;
class Texture;

////////////////////////////////////////////////////////////////////////////////
/// \brief A window for displaying stuff.
///
/// It's a window which can display OpenGL stuff.
////////////////////////////////////////////////////////////////////////////////
class RenderWindow {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief A description of a window.
        ///
        /// Used when creating a window.
        ////////////////////////////////////////////////////////////////////////
        struct Description {

            ////////////////////////////////////////////////////////////////////
            /// \brief Constructor.
            ///
            /// Creates a new window description.
            ///
            /// \param width                The width of the window.
            /// \param height               The height of the window.
            /// \param title                The title of the window.
            /// \param display              The X display where the window
            ///                             should open.
            /// \param stereo_mode          The stereo mode used for the window.
            /// \param warp_matrices_path   An absolute path to a directory
            ///                             where warp matrices are stored.
            ///                             "" if no warping is desired.
            ////////////////////////////////////////////////////////////////////
            Description(int width, int height, std::string const& title,
                        std::string const& display,
                        StereoMode stereo_mode = MONO,
                        std::string const& warp_matrices_path=""):
                width_(width), height_(height),
                title_(title),
                display_(display),
                stereo_mode_(stereo_mode),
                warp_matrices_path_(warp_matrices_path) {}

            ////////////////////////////////////////////////////////////////////
            /// \brief The width of the window.
            ////////////////////////////////////////////////////////////////////
            int width_;

            ////////////////////////////////////////////////////////////////////
            /// \brief The height of the window.
            ////////////////////////////////////////////////////////////////////
            int height_;

            ////////////////////////////////////////////////////////////////////
            /// \brief The title of the window.
            ////////////////////////////////////////////////////////////////////
            std::string title_;

            ////////////////////////////////////////////////////////////////////
            /// \brief The X display where the window should opened.
            ////////////////////////////////////////////////////////////////////
            std::string display_;

            ////////////////////////////////////////////////////////////////////
            /// \brief The stereo mode used for the window.
            ////////////////////////////////////////////////////////////////////
            StereoMode stereo_mode_;

            ////////////////////////////////////////////////////////////////////
            /// \brief An absolute path to a directory where warp matrices are
            ///        stored.
            ///
            /// "" if no warping is desired.
            ////////////////////////////////////////////////////////////////////
            std::string warp_matrices_path_;
        };

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new RenderWindow. It owns a RenderContext where Geomtries
        /// can be drawn to.
        ///
        /// \param description   The description of the window.
        ////////////////////////////////////////////////////////////////////////
        RenderWindow(Description const& description);

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
        /// \param texture          The Texture to be drawn.
        ////////////////////////////////////////////////////////////////////////
        void display_mono(std::shared_ptr<Texture> const& texture);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Draws the given Textures to the window.
        ///
        /// The given Textures are drawn to the window. They are drawn according
        /// to the given stereo mode.
        ///
        /// \param left_texture     The left eye texture.
        /// \param right_texture    The reight eye exture.
        /// \param stereo_mode      The stereo mode for mapping both textures.
        /// \param bottom_left      Relative coords of the bottom left corner.
        /// \param top_right        Relative coordinates of the top right corner.
        ////////////////////////////////////////////////////////////////////////
        void display_stereo(std::shared_ptr<Texture> const& left_texture,
                            std::shared_ptr<Texture> const& right_texture,
                            StereoMode stereo_mode,
                            math::vec2 const& bottom_left = math::vec2(0, 0),
                            math::vec2 const& size = math::vec2(1, 1));

        ////////////////////////////////////////////////////////////////////////
        ///
        ////////////////////////////////////////////////////////////////////////
        void display_preview(std::shared_ptr<Texture> const& texture);

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
        mutable unsigned preview_count_;

        RenderContext ctx_;

        ShaderProgram fullscreen_shader_;
        scm::gl::quad_geometry_ptr fullscreen_quad_;

        scm::gl::depth_stencil_state_ptr depth_stencil_state_;

        WarpMatrix *warpRR_, *warpGR_, *warpBR_,
                   *warpRL_, *warpGL_, *warpBL_;
};

}

#endif // GUA_RENDERWINDOW_HPP
