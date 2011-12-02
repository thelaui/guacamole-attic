#ifndef RENDERER_HPP
#define RENDERER_HPP

class Renderer {
    public:
        Renderer();
        virtual ~Renderer();

        void open_display( int width, int height, std::string const& display = ":0.0" );

        void start_render_loop( SceneGraph const* scene_graph );

    private:

};

#endif // RENDERER_HPP
