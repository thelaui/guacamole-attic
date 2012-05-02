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

gua::RenderPipeline* create_pipe() {
    // setup rendering pipeline
    auto g_buffer_mirror = new gua::RenderPass("g_buffer_mirror", "mirror_camera", "floor_screen", "!floor & !lights", 0.5, 0.5);
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("color", 0));
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("normal", 1));
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("specular_emit", 2));
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("position", 3));
    g_buffer_mirror->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto lighting_mirror = new gua::FullscreenPass("lighting_mirror", "mirror_camera", "floor_screen", "deferred_lighting", "lights & box", 0.5, 0.5);
    lighting_mirror->add_buffer(gua::ColorBufferDescription("color", 0));
    lighting_mirror->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    lighting_mirror->set_input_buffer("g_buffer_mirror", "color", "tex_color");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "normal", "tex_normal");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "specular_emit", "tex_specular_emit");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "position", "tex_position");

    auto g_buffer = new gua::RenderPass("g_buffer", "camera", "screen", "!lights");
    g_buffer->add_buffer(gua::ColorBufferDescription("color", 0));
    g_buffer->add_buffer(gua::ColorBufferDescription("normal", 1));
    g_buffer->add_buffer(gua::ColorBufferDescription("specular_emit", 2));
    g_buffer->add_buffer(gua::ColorBufferDescription("position", 3));
    g_buffer->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    g_buffer->set_input_buffer("lighting_mirror", "color", "mirror_tiles", "tex_mirror");

    auto lighting = new gua::FullscreenPass("lighting", "camera", "screen", "deferred_lighting", "lights & box");
    lighting->add_buffer(gua::ColorBufferDescription("color", 0));
    lighting->set_input_buffer("g_buffer", "color", "tex_color");
    lighting->set_input_buffer("g_buffer", "normal", "tex_normal");
    lighting->set_input_buffer("g_buffer", "specular_emit", "tex_specular_emit");
    lighting->set_input_buffer("g_buffer", "position", "tex_position");

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, "deferred_example", ":0.0", gua::MONO));
    pipe->add_render_pass(g_buffer);
    pipe->add_render_pass(g_buffer_mirror);
    pipe->add_render_pass(lighting);
    pipe->add_render_pass(lighting_mirror);
    pipe->set_final_buffer("lighting", "color");

    return pipe;
}

std::vector<gua::SceneGraph::Iterator> add_lights(gua::SceneGraph& graph, int count) {

    std::vector<gua::SceneGraph::Iterator> lights(count);

    auto sphere_core = new gua::GeometryCore("light_sphere", "bright");

    for (int i(0); i<count; ++i) {
        auto light_core = new gua::LightCore(gua::Color3f::random());

        lights[i] = graph.add_node("/", "sphere"+gua::string_utils::to_string(i), sphere_core);
        lights[i].scale(0.02, 0.02, 0.02);
        lights[i].translate(gua::randomizer::random(-0.7f, 0.7f), gua::randomizer::random(0.05f, 0.1f), gua::randomizer::random(-0.7f, 0.7f));
        lights[i].add_to_group("box");

        auto light = lights[i].add_child("light", light_core);
        light.scale(40, 40, 40);
        light.add_to_group("lights");
    }

    return lights;
}

int main(int argc, char** argv) {
    // initialize guacamole
    gua::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

    // setup scene
    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "mirror_tiles");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(2, 1, 2);
    floor.add_to_group("floor");

    auto floor_mirror_screen_core(new gua::ScreenCore(2, 2));
    auto floor_screen = graph.add_node("/", "floor_screen", floor_mirror_screen_core);
    floor_screen.rotate(90, 1, 0, 0);

    auto cube_core = new gua::GeometryCore("cube", "tiles");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, 0);
    box.add_to_group("box");

    auto sky_core = new gua::GeometryCore("sky_sphere", "sky");
    auto sky = graph.add_node("/", "sky", sky_core);
    sky.scale(50, 50, 50);
    box.add_to_group("box");

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 1);

    auto lights = add_lights(graph, 20);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);

    camera = graph.add_node("/screen/camera", "mirror_camera", camera_core);
    camera.translate(0, -0.9, 0);

    gua::RenderServer renderer({create_pipe()});

    gua::Timer timer;
    timer.start();

    // application loop
    while (true) {
        renderer.queue_draw(&graph);

        float time(timer.get_elapsed());

        for (int i=0; i<lights.size(); ++i) {
            lights[i].translate(0, std::sin(time*(i*0.1 + 0.5))*0.001, 0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        graph["/screen"].rotate(0.03, 0, 1, 0);
    }

    return 0;
}
