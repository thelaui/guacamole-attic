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
/// \brief Declaration of the RenderPipeline class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_PIPELINE_HPP
#define RENDER_PIPELINE_HPP


#include <map>

#include "renderer/RenderWindow.hpp"

namespace gua {

class GenericRenderPass;
class SceneGraph;

class RenderPipeline {
    public:
        RenderPipeline(RenderWindow::Description const& window);
        ~RenderPipeline();

        void add_render_pass(GenericRenderPass* pass);
        GenericRenderPass* get_render_pass(std::string const& pass_name);

        SceneGraph const* get_current_graph() const;
        RenderContext const& get_context() const;

        void set_final_buffer(std::string const& pass_name, std::string const& buffer_name);

        StereoMode get_stereo_mode() const;

        float get_application_fps() const;
        float get_rendering_fps() const;

        friend class RenderClient;

    private:
        void process(SceneGraph* graph, float application_fps, float rendering_fps);
        void create_buffers();

        RenderWindow* window_;
        RenderWindow::Description window_description_;
        std::string final_pass_, final_buffer_;
        std::map<std::string, GenericRenderPass*> passes_;

        SceneGraph* current_graph_;

        float application_fps_, rendering_fps_;
};

}

#endif // RENDER_PIPELINE_HPP



