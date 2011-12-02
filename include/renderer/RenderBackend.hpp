#ifndef RENDER_BACKEND_HPP
#define RENDER_BACKEND_HPP

class RenderBackend {
    public:
        RenderBackend( int width, int height, std::string const& display = ":0.0" );
        virtual ~RenderBackend();

        void render( std::vector<Geometry*> const& node_list,
                     std::vector<Light*> const& light_list,
                     Camera const& camera );

    private:

};

#endif // RENDER_BACKEND_HPP
