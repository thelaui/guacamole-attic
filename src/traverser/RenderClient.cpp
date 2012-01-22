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
#include "include/traverser/RenderClient.hpp"

#include "include/scenegraph/SceneGraph.hpp"
#include "include/renderer/RenderBackend.hpp"

namespace gua {

RenderClient::RenderClient(int width, int height, std::string const& camera, std::string const& display):
    draw_thread_(NULL),
    render_backend_(NULL),
    width_(width),
    height_(height),
    camera_(camera),
    display_(display) {}

RenderClient::~RenderClient() {
    if (draw_thread_) {
        draw_thread_->detach();
        delete draw_thread_;
    }

    if (render_backend_)
        delete render_backend_;
}

void RenderClient::queue_draw(OptimizedScene const& scene) {

    current_scene_ = scene;

    if(!draw_thread_)
        draw_thread_ = new std::thread(&RenderClient::draw_loop, this);


}

std::string const& RenderClient::get_camera_name() const {
    return camera_;
}

void RenderClient::draw_loop() {
    if (!render_backend_)
        render_backend_ = new RenderBackend(width_, height_, display_);

    while (true) {
        auto camera = current_scene_.cameras_.find(camera_);

        if (camera != current_scene_.cameras_.end()) {
            render_backend_->render(current_scene_.nodes_, current_scene_.lights_, camera->second);
        }
    }
}

}

