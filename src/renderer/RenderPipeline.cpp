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

#include "renderer/RenderPass.hpp"

namespace gua {

RenderPipeline::RenderPipeline(RenderWindow::Description const& window, StereoMode stereo_mode):
    window_(window),
    stereo_mode_(stereo_mode),
    passes_() {}

void RenderPipeline::add_render_pass(RenderPass* pass) {
    pass->set_pipeline(this);
    passes_[pass->get_name()] = pass;
}

RenderPass* RenderPipeline::get_render_pass(std::string const& pass_name) {
    return passes_[pass_name];
}

RenderContext const& RenderPipeline::get_context() const {
    return window_.get_context();
}

void RenderPipeline::set_final_buffer(std::string const& pass_name, std::string const& buffer_name) {
    final_pass_ = pass_name;
    final_buffer_ = buffer_name;
}

void RenderPipeline::process(SceneGraph const& graph) {
    window_.display_texture(passes_[final_pass_]->get_buffer(final_buffer_));
}

void RenderPipeline::flush() {
    for (auto& pass: passes_)
        pass.second->flush();
}

}



