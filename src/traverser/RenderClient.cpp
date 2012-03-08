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
#include "utils/Timer.hpp"
#include "utils/debug.hpp"

namespace gua {

RenderClient::RenderClient(int width, int height, std::string const& camera, std::string const& screen, std::string const& display):
    draw_thread_(NULL),
    render_backend_(NULL),
    rendering_finished_(false),
    render_mutex_(),
    render_condition_(),
    width_(width),
    height_(height),
    camera_(camera),
    screen_(screen),
    display_(display),
    frame_(0) {}

RenderClient::~RenderClient() {
    if (draw_thread_) {
        draw_thread_->detach();
        delete draw_thread_;
    }

    if (render_backend_)
        delete render_backend_;
}

void RenderClient::queue_draw(OptimizedScene const& scene) {
    if(!draw_thread_)
        draw_thread_ = new std::thread(&RenderClient::draw_loop, this);

    // lock rendering
    std::unique_lock<std::mutex> lock(render_mutex_);

    if (rendering_finished_) {
        current_scene_ = scene;
        rendering_finished_ = false;
        // signal
        render_condition_.notify_one();
    }
}

std::string const& RenderClient::get_camera_name() const {
    return camera_;
}

void RenderClient::draw_loop() {
    if (!render_backend_)
        render_backend_ = new RenderBackend(width_, height_, camera_, screen_, display_);

    Timer timer;
    timer.start();

    while (true) {
        if (++frame_ % 100 == 0) {
            DEBUG("Renderer FPS: %f", frame_/timer.get_elapsed());
            frame_ = 0;
            timer.reset();
        }

        render_backend_->render(current_scene_);

        // lock rendering
        std::unique_lock<std::mutex> lock(render_mutex_);

        rendering_finished_ = true;

        // unlock rendering and wait
        render_condition_.wait(lock);
    }
}

}

