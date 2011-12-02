#include "include/renderer/RenderWindow.hpp"

#include <sstream>

#include "include/utils/debug.hpp"
#include "include/drawer.hpp"

RenderWindow::RenderWindow(std::string const& display) throw (std::string):
    frames_(0),
    framesStart_(0),
    frameCount_(0) {
    ///////////////////////////////////////////////
    // Open X display
    ///////////////////////////////////////////////

    ctx_.display = XOpenDisplay(display.c_str());
    ctx_.width = 1600;
    ctx_.height = 900;

    GLint nMajorVer = 0;
    GLint nMinorVer = 0;
    glXQueryVersion(ctx_.display, &nMajorVer, &nMinorVer);
    MESSAGE("Supported GLX version - %d.%d", nMajorVer, nMinorVer);

    if(nMajorVer == 1 && nMinorVer < 2)
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

    XSetStandardProperties(ctx_.display, ctx_.window, "MultiPipe", "folder", None, NULL, 0, NULL);

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

//    if (!glXJoinSwapGroupNV(ctx_.display, ctx_.window, 101))
//        throw std::string("Failed to join swap group");

    glXMakeCurrent(ctx_.display, None, NULL);
}

RenderWindow::~RenderWindow() {
    glXMakeCurrent(ctx_.display, None, NULL);

    glXDestroyContext(ctx_.display, ctx_.context);
    ctx_.context = NULL;

    XDestroyWindow(ctx_.display, ctx_.window);
    ctx_.window = 0;

    XCloseDisplay(ctx_.display);
    ctx_.display = 0;
}

void RenderWindow::draw(Scene* scene) {
    glXMakeCurrent(ctx_.display, ctx_.window, ctx_.context);

    drawer_.init(&ctx_, scene, std::rand());

    auto time = std::chrono::system_clock::now();
    auto since_epoch = time.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
    framesStart_ = millis.count();

    while(true) {
        drawer_.draw();
        ++frameCount_;

        if (++frames_ == 100) {
            auto time = std::chrono::system_clock::now();
            auto since_epoch = time.time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
            auto now = millis.count();

            double fps = 1000.0*frames_/static_cast<double>(now - framesStart_);

            std::stringstream sstr;
            sstr << "FPS: " << fps << "     Faces: " << drawer_.faceCount() << "     Frame: " << frameCount_;
            std::string fpsString(sstr.str());

            XStoreName(ctx_.display, ctx_.window, fpsString.c_str());
            XFlush(ctx_.display);

            framesStart_ = now;
            frames_ = 0;
        }
    }
}
