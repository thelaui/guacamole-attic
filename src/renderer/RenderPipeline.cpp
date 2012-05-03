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
/// \brief Implementation of the RenderPipeline class.
////////////////////////////////////////////////////////////////////////////////

#include "renderer/RenderPipeline.hpp"

#include "renderer/GenericRenderPass.hpp"
#include "utils/debug.hpp"

#include "renderer/TextureBase.hpp"
#include "renderer/WarpMatrix.hpp"

#include <iostream>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

RenderPipeline::
RenderPipeline(RenderWindow::Description const& window):

    window_(NULL),
    window_description_(window),
    passes_(),
    current_graph_(NULL),
    application_fps_(0.f), rendering_fps_(0.f) {}

////////////////////////////////////////////////////////////////////////////////

RenderPipeline::
~RenderPipeline() {

    if(window_)
        delete window_;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
add_render_pass(GenericRenderPass* pass) {

    pass->set_pipeline(this);
    passes_[pass->get_name()] = pass;
}

////////////////////////////////////////////////////////////////////////////////

GenericRenderPass* RenderPipeline::
get_render_pass(std::string const& pass_name) {

    return passes_[pass_name];
}

////////////////////////////////////////////////////////////////////////////////

SceneGraph const* RenderPipeline::
get_current_graph() const {

    return current_graph_;
}

////////////////////////////////////////////////////////////////////////////////

RenderContext const& RenderPipeline::
get_context() const {

    if (!window_)
        ERROR("Failed to return Context, the RenderWindow has not been \
              initialized yet!");

    return window_->get_context();
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
set_final_buffer(std::string const& pass_name,
                 std::string const& buffer_name) {

    final_pass_ = pass_name;
    final_buffer_ = buffer_name;
}

////////////////////////////////////////////////////////////////////////////////

StereoMode RenderPipeline::
get_stereo_mode() const {

    return window_description_.stereo_mode;
}

////////////////////////////////////////////////////////////////////////////////

float RenderPipeline::
get_application_fps() const {

    return application_fps_;
}

////////////////////////////////////////////////////////////////////////////////

float RenderPipeline::
get_rendering_fps() const {

    return rendering_fps_;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
process(SceneGraph* graph, float application_fps, float rendering_fps) {

    current_graph_ = graph;
    application_fps_ = application_fps;
    rendering_fps_ = rendering_fps;

    if(!window_) {
        window_ = new RenderWindow(window_description_);
        create_buffers();
    }

    window_->set_active(true);
    window_->start_frame();

    if (window_description_.stereo_mode == MONO) {
        window_->display_mono(passes_[final_pass_]->get_buffer(final_buffer_,
                                                               CENTER, true));
    } else {
        window_->display_stereo(passes_[final_pass_]->get_buffer(final_buffer_,
                                                               LEFT, true),
                                passes_[final_pass_]->get_buffer(final_buffer_,
                                                               RIGHT, true),
                                window_description_.stereo_mode);
    }

    window_->finish_frame();

    for (auto& pass: passes_)
        pass.second->flush();
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
create_buffers() {

    for (auto& pass: passes_)
        pass.second->create_buffers(window_description_.stereo_mode);
}

////////////////////////////////////////////////////////////////////////////////

}



