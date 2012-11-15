////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
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
/// \brief Definition of the RenderPipeline class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/RenderPipeline.hpp"

// guacamole headers
#include "renderer/GenericRenderPass.hpp"
#include "utils/debug.hpp"
#include "renderer/TextureBase.hpp"
#include "renderer/WarpMatrix.hpp"

// external headers
#include <iostream>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

RenderPipeline::
RenderPipeline(RenderWindow::Description const& window):

    window_(NULL),
    window_description_(window),
    passes_(),
    current_graph_(NULL),
    application_fps_(0.f), rendering_fps_(0.f) {

    }

////////////////////////////////////////////////////////////////////////////////

RenderPipeline::
~RenderPipeline() {

    if(window_)
        delete window_;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
add_render_pass(GenericRenderPass* pass) {

    if (passes_.find(pass->get_name()) == passes_.end()) {
        pass->set_pipeline(this);
        passes_[pass->get_name()] = pass;
    } else {
        WARNING("Failed to add pass \"%s\" to pipe: A pass with "
                "this name already exists!", pass->get_name().c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////

GenericRenderPass* RenderPipeline::
get_render_pass(std::string const& pass_name) {

    auto pass(passes_.find(pass_name));

    if (pass == passes_.end()) {
        WARNING("Failed to get pass \"%s\" to pipe: A pass with "
                "this name does not exist!", pass_name.c_str());
        return NULL;
    }

    return pass->second;
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
        ERROR("Failed to return Context, the RenderWindow has not been "
              "initialized yet!");

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

void RenderPipeline::
add_preview_buffer(std::string const& pass_name,
                   std::string const& buffer_name) {

    preview_buffers_.push_back(std::make_pair(pass_name, buffer_name));
}

////////////////////////////////////////////////////////////////////////////////

StereoMode RenderPipeline::
get_stereo_mode() const {

    return window_description_.stereo_mode_;
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

    auto it(passes_.find(final_pass_));

    if (it != passes_.end()) {

        auto pass(it->second);

        if (window_description_.stereo_mode_ == MONO) {
            window_->display_mono(pass->get_buffer(final_buffer_, CENTER, true));
        } else {
            window_->display_stereo(pass->get_buffer(final_buffer_, LEFT, true),
                                    pass->get_buffer(final_buffer_, RIGHT, true),
                                    window_description_.stereo_mode_);
        }
    } else {
        WARNING("Failed to display buffer \"%s\" from pass \"%s\": A pass "
                "with this name does not exist!", final_buffer_.c_str(),
                final_pass_.c_str());
    }

    for (auto buffer : preview_buffers_) {
        auto it(passes_.find(buffer.first));

        if (it != passes_.end()) {

            auto pass(it->second);

            if (window_description_.stereo_mode_ == MONO) {
                window_->display_preview(pass->get_buffer(buffer.second, CENTER, true));
            } else {
                window_->display_preview(pass->get_buffer(buffer.second, LEFT, true));
            }
        } else {
            WARNING("Failed to display buffer \"%s\" from pass \"%s\": A pass "
                    "with this name does not exist!", buffer.second.c_str(),
                    buffer.first.c_str());
        }
    }

    window_->finish_frame();

    for (auto& pass: passes_)
        pass.second->flush();
}

////////////////////////////////////////////////////////////////////////////////

void RenderPipeline::
create_buffers() {

    for (auto& pass: passes_)
        pass.second->create_buffers(window_description_.stereo_mode_);
}

////////////////////////////////////////////////////////////////////////////////

}



