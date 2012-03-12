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
/// \brief Definition of the Render class.
////////////////////////////////////////////////////////////////////////////////
#include "traverser/RenderClient.hpp"

#include "scenegraph/SceneGraph.hpp"
#include "renderer/RenderBackend.hpp"
#include "renderer/RenderPipeline.hpp"
#include "utils/Timer.hpp"
#include "utils/debug.hpp"

namespace gua {

RenderClient::RenderClient(RenderPipeline* pipeline):
    draw_thread_(NULL),
    render_pipeline_(pipeline),
    rendering_finished_(false),
    render_mutex_(),
    render_condition_(),
    frame_(0) {}

RenderClient::~RenderClient() {
    if (draw_thread_) {
        draw_thread_->detach();
        delete draw_thread_;
    }
}

void RenderClient::queue_draw(SceneGraph const* graph) {
    if(!draw_thread_) {
        graph_copy_ = *graph;
        draw_thread_ = new std::thread(&RenderClient::draw_loop, this);
    }

    // lock rendering
    std::unique_lock<std::mutex> lock(render_mutex_);

    if (rendering_finished_) {
        graph_copy_ = *graph;
        rendering_finished_ = false;
        // signal
        render_condition_.notify_one();
    }
}

void RenderClient::draw_loop() {
    Timer timer;
    timer.start();

    while (true) {
        if (++frame_ % 100 == 0) {
            DEBUG("Renderer FPS: %f", frame_/timer.get_elapsed());
            frame_ = 0;
            timer.reset();
        }

        // render
        render_pipeline_->process(&graph_copy_);

        // lock rendering
        std::unique_lock<std::mutex> lock(render_mutex_);

        rendering_finished_ = true;

        // unlock rendering and wait
        render_condition_.wait(lock);
    }
}

}

