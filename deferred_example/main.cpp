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
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("specular", 2));
    g_buffer_mirror->add_buffer(gua::ColorBufferDescription("position", 3));
    g_buffer_mirror->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto lighting_mirror = new gua::RenderPass("lighting_mirror", "mirror_camera", "floor_screen", "lights | camerastuff", 0.5, 0.5);
    lighting_mirror->add_buffer(gua::ColorBufferDescription("color", 0));
    lighting_mirror->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    lighting_mirror->set_input_buffer("g_buffer_mirror", "color", "deferred_lighting", "tex_color");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "normal", "deferred_lighting", "tex_normal");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "specular", "deferred_lighting", "tex_specular");
    lighting_mirror->set_input_buffer("g_buffer_mirror", "position", "deferred_lighting", "tex_position");
    lighting_mirror->overwrite_uniform_float("deferred_lighting", "texel_width", 2.0/800);
    lighting_mirror->overwrite_uniform_float("deferred_lighting", "texel_height", 2.0/600);

    auto g_buffer = new gua::RenderPass("g_buffer", "camera", "screen", "!lights");
    g_buffer->add_buffer(gua::ColorBufferDescription("color", 0));
    g_buffer->add_buffer(gua::ColorBufferDescription("normal", 1));
    g_buffer->add_buffer(gua::ColorBufferDescription("specular", 2));
    g_buffer->add_buffer(gua::ColorBufferDescription("position", 3));
    g_buffer->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    g_buffer->set_input_buffer("lighting_mirror", "color", "mirror_tiles", "tex_mirror");

    auto lighting = new gua::RenderPass("lighting", "camera", "screen", "lights | camerastuff");
    lighting->add_buffer(gua::ColorBufferDescription("color", 0));
    lighting->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    lighting->set_input_buffer("g_buffer", "color", "deferred_lighting", "tex_color");
    lighting->set_input_buffer("g_buffer", "normal", "deferred_lighting", "tex_normal");
    lighting->set_input_buffer("g_buffer", "specular", "deferred_lighting", "tex_specular");
    lighting->set_input_buffer("g_buffer", "position", "deferred_lighting", "tex_position");

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(800, 600, "deferred_example", ":0.0", gua::ANAGLYPH_RED_CYAN));
    pipe->add_render_pass(g_buffer);
    pipe->add_render_pass(g_buffer_mirror);
    pipe->add_render_pass(lighting);
    pipe->add_render_pass(lighting_mirror);
    pipe->set_final_buffer("lighting", "color");

    return pipe;
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
    floor_screen.add_to_group("camerastuff");

    auto cube_core = new gua::GeometryCore("cube", "tiles");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, 0);
    box.add_to_group("box");

    auto screen_core(new gua::ScreenCore(1.6, 1.2));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 1);
    screen.add_to_group("camerastuff");

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);
    camera.add_to_group("camerastuff");

    camera = graph.add_node("/screen/camera", "mirror_camera", camera_core);
    camera.translate(0, -0.9, 0);
    camera.add_to_group("camerastuff");

    auto light_core = new gua::GeometryCore("light_sphere", "deferred_lighting");
    auto light = graph.add_node("/", "light1", light_core);
    light.scale(10, 10, 10);
    light.translate(0.3, 0.1, -0.2);
    light.add_to_group("lights");

    light = graph.add_node("/", "light4", light_core);
    light.scale(15, 15, 15);
    light.translate(-0.3, 0.5, 0.4);
    light.add_to_group("lights");

    gua::MaterialBase::instance()->get("deferred_lighting")->set_uniform_float("texel_width", 1.0/800);
    gua::MaterialBase::instance()->get("deferred_lighting")->set_uniform_float("texel_height", 1.0/600);
    gua::MaterialBase::instance()->get("deferred_lighting")->set_uniform_float("x_fragment_offset", 0);
    gua::MaterialBase::instance()->get("deferred_lighting")->set_blend_state(scm::gl::blend_state_desc(
                                                                             scm::gl::blend_ops(true, scm::gl::FUNC_ONE, scm::gl::FUNC_ONE, scm::gl::FUNC_ONE, scm::gl::FUNC_ONE)));
    gua::MaterialBase::instance()->get("deferred_lighting")->set_rasterizer_state(scm::gl::rasterizer_state_desc(scm::gl::FILL_SOLID, scm::gl::CULL_FRONT));
    gua::MaterialBase::instance()->get("deferred_lighting")->set_depth_stencil_state(scm::gl::depth_stencil_state_desc(false, false));



    gua::RenderServer renderer({create_pipe()});

    // application loop
    while (true) {
        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        graph["/screen"].rotate(0.3, 0, 1, 0);
    }

    return 0;
}
