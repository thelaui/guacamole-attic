#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "include/renderer/RenderWindow.hpp"

class SceneGraph;

class Renderer {
    public:
        Renderer(int width, int height, std::string const& display = ":0.0") {}
        virtual ~Renderer() {}

        void start_render_loop( SceneGraph const& scene_graph ) {}

    private:

};

#endif // RENDERER_HPP
