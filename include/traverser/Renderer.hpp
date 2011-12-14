#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>
#include <string>

#include "include/renderer/RenderWindow.hpp"

class SceneGraph;
class Optimizer;
class RenderBackend;

class Renderer {
    public:
        Renderer(int width, int height, std::string const& display = ":0.0");
        virtual ~Renderer();

		void start_render_loop( SceneGraph const* scene_graph );

	private:
		std::vector<RenderBackend*> render_backend_list_;
		Optimizer* optimizer_;
};

#endif // RENDERER_HPP
