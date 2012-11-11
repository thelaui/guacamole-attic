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
/// \brief Definition of the RenderClient class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "traverser/RenderClient.hpp"

// guacamole headers
#include "scenegraph/SceneGraph.hpp"
#include "renderer/RenderPipeline.hpp"
#include "utils/Timer.hpp"
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

RenderClient::
RenderClient(RenderPipeline* pipeline):
    draw_thread_(NULL),
    render_pipeline_(pipeline),
    graph_copy1_(),
    graph_copy2_(),
    application_fps_(0.f), rendering_fps_(0.f),
    application_frame_count_(0), rendering_frame_count_(0),
    application_timer_(), rendering_timer_(),
    rendering_copy1_(true),
    new_graph_available_(false),
    copy_mutex_() {}

////////////////////////////////////////////////////////////////////////////////

RenderClient::
~RenderClient() {

    if (draw_thread_) {
        draw_thread_->detach();
        delete draw_thread_;
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderClient::
queue_draw(SceneGraph const* graph) {

    if(!draw_thread_) {
        application_timer_.start();
        rendering_timer_.start();

        graph_copy1_ = *graph;
        graph_copy2_ = *graph;
        draw_thread_ = new std::thread(&RenderClient::draw_loop, this);
    }

    if (++application_frame_count_ == 100) {
        application_fps_ = 100.f/application_timer_.get_elapsed();
        application_timer_.reset();
        application_frame_count_ = 0;
    }

    // lock rendering
    std::unique_lock<std::mutex> lock(copy_mutex_);
    new_graph_available_ = true;

    if (rendering_copy1_) {
        graph_copy2_ = *graph;
    } else {
        graph_copy1_ = *graph;
    }
}

////////////////////////////////////////////////////////////////////////////////

void RenderClient::
draw_loop() {

    while (true) {

        // render
        if (rendering_copy1_) {
            render_pipeline_->process(
                               &graph_copy1_, application_fps_, rendering_fps_);
        } else {
            render_pipeline_->process(
                               &graph_copy2_, application_fps_, rendering_fps_);
        }


        if (++rendering_frame_count_ == 100) {
            rendering_fps_ = 100.f/rendering_timer_.get_elapsed();
            rendering_timer_.reset();
            rendering_frame_count_ = 0;
        }

        // lock rendering
        std::unique_lock<std::mutex> lock(copy_mutex_);

        if (new_graph_available_) {
            new_graph_available_ = false;
            rendering_copy1_ = !rendering_copy1_;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

}

