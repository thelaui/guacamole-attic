#ifndef RENDERER_HPP
#define RENDERER_HPP

class SceneGraph;
class Optimizer;
class RenderBackend;

#include <vector>
#include <string>

class Renderer {
	public:
		Renderer();
		virtual ~Renderer();

		void open_display( int width, int height, std::string const& display = ":0.0" );
		void start_render_loop( SceneGraph const* scene_graph );

	private:
		std::vector<RenderBackend*> render_backend_list_;
		Optimizer* optimizer_;
};

#endif // RENDERER_HPP
