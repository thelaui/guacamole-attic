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
/// \brief A simple example scene.
////////////////////////////////////////////////////////////////////////////////

#include "guacamole.hpp"

int main(int argc, char** argv) {
    // initialize guacamole
    gua::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

    // setup scene
    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "tiles");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(1.6, 1, 2);

    auto cube_core = new gua::GeometryCore("cube", "tiles_small");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, 0);

    auto monkey_core = new gua::GeometryCore("monkey", "wood");
    auto ape = graph.add_node("/box", "monkey", monkey_core);
    ape.scale(0.5, 0.5, 0.5);
    ape.translate(0, 1, 0);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 0.5);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);

    // setup rendering pipeline
    auto pass = new gua::RenderPass("main", "camera", "screen");
    pass->add_buffer(gua::ColorBufferDescription("color", 0));
    pass->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, "simple_example", ":0.0"), gua::ANAGLYPH_RED_CYAN);
    pipe->add_render_pass(pass);
    pipe->set_final_buffer("main", "color");

    gua::RenderServer renderer({pipe});

    // application loop
    while (true) {
        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        graph["/box/monkey"].rotate(2, 0, 1, 0);
        graph["/screen"].rotate(0.1, 0, 1, 0);
    }

    return 0;
}
