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
/// \brief Declaration of the RenderContext struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXT_HPP
#define RENDERCONTEXT_HPP

#include "renderer/glInclude.hpp"

#include <scm/gl_core/config.h>
#include <scm/gl_core/data_formats.h>
#include <scm/core.h>
#include <scm/gl_core.h>
#include <scm/gl_core/window_management/context.h>
#include <scm/gl_core/window_management/display.h>
#include <scm/gl_core/window_management/surface.h>
#include <scm/gl_core/window_management/window.h>

////////////////////////////////////////////////////////////////////////////////
/// \brief Information on a specific context.
///
/// Stores all relevant information on a OpenGL context.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

struct RenderContext {
    ////////////////////////////////////////////////////////////////////////////
    /// \brief The glx context of this RenderContext.
    ////////////////////////////////////////////////////////////////////////////
    scm::gl::wm::context_ptr context;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The X display where this context was opened.
    ////////////////////////////////////////////////////////////////////////////
    scm::gl::wm::display_ptr display;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The X window associated with this context.
    ////////////////////////////////////////////////////////////////////////////
    scm::gl::wm::window_ptr window;

    scm::gl::render_context_ptr render_context;

    scm::gl::render_device_ptr render_device;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The width of the window.
    ////////////////////////////////////////////////////////////////////////////
    int width;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief The height of the window.
    ////////////////////////////////////////////////////////////////////////////
    int height;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief A unique ID for this context.
    ////////////////////////////////////////////////////////////////////////////
    unsigned id;
};

}

#endif //RENDERCONTEXT_HPP
