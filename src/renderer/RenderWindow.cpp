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
/// \brief A database for accessing geometry data.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/RenderWindow.hpp"

#include "include/utils/debug.hpp"
#include "include/renderer/Geometry.hpp"

unsigned RenderWindow::last_context_id_ = 0;

RenderWindow::RenderWindow( int width, int height, std::string const& display ) throw (std::string):
    frames_(0),
    frame_count_(0),
    frames_start_(0) {

    ///////////////////////////////////////////////
    // Open X display
    ///////////////////////////////////////////////

    ctx_.display = XOpenDisplay(display.c_str());
    ctx_.width = width;
    ctx_.height = height;
    ctx_.id = last_context_id_++;

    int major_glx(0);
    int minor_glx(0);
    glXQueryVersion(ctx_.display, &major_glx, &minor_glx);
    MESSAGE("Supported GLX version - %i.%i", major_glx, minor_glx);

    if(major_glx == 1 && minor_glx < 2)
        throw std::string("GLX 1.2 or greater is necessary!");

    ///////////////////////////////////////////////
    // Configure Framebuffer
    ///////////////////////////////////////////////

    static int fbAttribs[] = {
        GLX_RENDER_TYPE,   GLX_RGBA_BIT,
        GLX_X_RENDERABLE,  True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER,  True,
        GLX_RED_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        0
    };

    int numConfigs = 0;
    GLXFBConfig* fbConfigs = glXChooseFBConfig(ctx_.display, DefaultScreen(ctx_.display), fbAttribs, &numConfigs);
    XVisualInfo* visualInfo = glXGetVisualFromFBConfig(ctx_.display, fbConfigs[0]);

    ///////////////////////////////////////////////
    // Create an X window
    ///////////////////////////////////////////////

    XSetWindowAttributes winAttribs;
    winAttribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;

    winAttribs.border_pixel = 0;
    winAttribs.bit_gravity = StaticGravity;
    winAttribs.colormap = XCreateColormap(ctx_.display, RootWindow(ctx_.display, visualInfo->screen),
                                          visualInfo->visual, AllocNone);

    GLint winmask = CWBorderPixel | CWBitGravity | CWEventMask| CWColormap;

    ctx_.window = XCreateWindow(ctx_.display, DefaultRootWindow(ctx_.display), 20, 20,
                 ctx_.width, ctx_.height, 0, visualInfo->depth, InputOutput, visualInfo->visual, winmask, &winAttribs);

    if (ctx_.window == 0)
        throw std::string("Failed to create X window!");

    XSetStandardProperties(ctx_.display, ctx_.window, "guacamole", "folder", None, NULL, 0, NULL);

    XMapWindow(ctx_.display, ctx_.window);

    ///////////////////////////////////////////////
    // Create the context
    ///////////////////////////////////////////////

    GLint attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 1,
        //GLX_CONTEXT_PROFILE_MASK_ARB,GLX_CONTEXT_CORE_PROFILE_BIT_ARB, 0          // for 3.1
        GLX_CONTEXT_PROFILE_MASK_ARB,GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0   // for 4.1
    };

    ctx_.context = glXCreateContextAttribsARB(ctx_.display, fbConfigs[0], 0, True, attribs);
    if (!glXMakeCurrent(ctx_.display, ctx_.window, ctx_.context))
        throw std::string("Failed to make context current!");

    ///////////////////////////////////////////////
    // Initialize GLEW
    ///////////////////////////////////////////////

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
        throw std::string("Failed to initialize GLEW!");

    if (!glxewIsSupported("GLX_NV_swap_group"))
        throw std::string("Swap groups are not supported!");

    if (!glXJoinSwapGroupNV(ctx_.display, ctx_.window, 101))
        throw std::string("Failed to join swap group");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    //glXMakeCurrent(ctx_.display, None, NULL);
}

RenderWindow::~RenderWindow() {
    glXMakeCurrent(ctx_.display, None, NULL);
    glXDestroyContext(ctx_.display, ctx_.context);
    XDestroyWindow(ctx_.display, ctx_.window);
    XCloseDisplay(ctx_.display);
}

void RenderWindow::set_active() const {
    glXMakeCurrent(ctx_.display, ctx_.window, ctx_.context);
}

void RenderWindow::start_frame() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderWindow::finish_frame() const {
    glXSwapBuffers(ctx_.display, ctx_.window);
}

void RenderWindow::draw(std::shared_ptr<Geometry> geometry) const {
    geometry->draw(ctx_);
}

void RenderWindow::init() {
    XInitThreads();
    glXCreateContextAttribsARB = (GLXContext(*)(Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int *attrib_list))glXGetProcAddressARB((GLubyte*)"glXCreateContextAttribsARB");
    glXChooseFBConfig = (GLXFBConfig*(*)(Display *dpy, int screen, const int *attrib_list, int *nelements))glXGetProcAddressARB((GLubyte*)"glXChooseFBConfig");
    glXGetVisualFromFBConfig = (XVisualInfo*(*)(Display *dpy, GLXFBConfig config))glXGetProcAddressARB((GLubyte*)"glXGetVisualFromFBConfig");
}

RenderContext const& RenderWindow::get_context() const {
    return ctx_;
}