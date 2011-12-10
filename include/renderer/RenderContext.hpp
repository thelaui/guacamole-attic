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
/// \brief A struct storing all information on a OpenGL context.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERCONTEXT_HPP
#define RENDERCONTEXT_HPP

#include "include/renderer/glInclude.hpp"

struct RenderContext {
    GLXContext context;
    Display *display;
    Window window;
    int width;
    int height;
    unsigned id;
};

#endif //RENDERCONTEXT_HPP
