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
/// \brief A simple example scene.
////////////////////////////////////////////////////////////////////////////////

#include "guacamole.hpp"

gua::RenderPipeline* create_pipe() {
    // setup rendering pipeline
    auto g_buffer_pass = new gua::RenderPass("g_buffer", "camera", "screen", "!lights");
    g_buffer_pass->add_buffer(gua::ColorBufferDescription("normal", 0));
    g_buffer_pass->add_buffer(gua::ColorBufferDescription("tex_coords_mat_id", 1));
    g_buffer_pass->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto l_buffer_pass = new gua::RenderPass("l_buffer", "camera", "screen", "lights");
    l_buffer_pass->add_buffer(gua::ColorBufferDescription("diffuse", 0));
    l_buffer_pass->add_buffer(gua::ColorBufferDescription("specular", 1));
    l_buffer_pass->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));
    l_buffer_pass->set_input_buffer("g_buffer", "normal", "point_light", "in_normal");
    l_buffer_pass->set_input_buffer("g_buffer", "tex_coords_mat_id", "point_light", "in_tex_coords_mat_id");
    l_buffer_pass->set_input_buffer("g_buffer", "depth_stencil", "point_light", "in_depth_stencil");

    auto final_pass = new gua::FullscreenPass("final", "camera", "screen", "final");
    final_pass->add_buffer(gua::ColorBufferDescription("color", 0));
    final_pass->set_input_buffer("l_buffer", "diffuse", "in_diffuse");
    final_pass->set_input_buffer("l_buffer", "specular", "in_specular");
    final_pass->set_input_buffer("g_buffer", "normal", "in_normal");
    final_pass->set_input_buffer("g_buffer", "tex_coords_mat_id", "in_tex_coords_mat_id");
    final_pass->set_input_buffer("g_buffer", "depth_stencil", "in_depth_stencil");

    auto post_process_pass = new gua::FullscreenPass("post_process", "camera", "screen", "post_process");
    post_process_pass->add_buffer(gua::ColorBufferDescription("color", 0));
    post_process_pass->set_input_buffer("final", "color", "in_color");
    post_process_pass->set_input_buffer("g_buffer", "depth_stencil", "in_depth_stencil");

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, "pipeline_ng", ":0.0", gua::MONO));
    pipe->add_render_pass(g_buffer_pass);
    pipe->add_render_pass(l_buffer_pass);
    pipe->add_render_pass(final_pass);
    pipe->add_render_pass(post_process_pass);
    pipe->set_final_buffer("post_process", "color");

    return pipe;
}

std::vector<gua::SceneGraph::Iterator> add_lights(gua::SceneGraph& graph, int count) {

    std::vector<gua::SceneGraph::Iterator> lights(count);

    auto sphere_core = new gua::GeometryCore("light_sphere", "point_light");
    auto dummy_core = new gua::GeometryCore("light_sphere", "light_dummy");

    for (int i(0); i<count; ++i) {
        lights[i] = graph.add_node("/", "sphere"+gua::string_utils::to_string(i), dummy_core);
        auto light = lights[i].add_child("light", sphere_core);
        light.add_to_group("lights");
        lights[i].scale(0.02, 0.02, 0.02);
        lights[i].translate(gua::randomizer::random(-0.8f, 0.8f), gua::randomizer::random(0.05f, 0.1f), gua::randomizer::random(-0.8f, 0.8f));

        light.scale(15, 15, 15);
    }

    return lights;
}

void add_monkeys(gua::SceneGraph& graph, int count) {

    auto monkey_core = new gua::GeometryCore("monkey", "wood");

    for (int i(0); i < count; ++i) {
        for (int j(0); j < count; ++j) {
            auto ape = graph.add_node("/", "monkey" + gua::string_utils::to_string(10 * i + j), monkey_core);
            ape.scale(0.1, 0.1, 0.1);
            ape.translate((i-count*0.5)*0.2, 0.4, (j-count*0.5)*0.2);
        }
    }
}

int main(int argc, char** argv) {

    // initialize guacamole
    gua::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

    auto light_mat = gua::MaterialBase::instance()->get("point_light");
    light_mat->set_blend_state(scm::gl::blend_state_desc(scm::gl::blend_ops(true, scm::gl::FUNC_ONE, scm::gl::FUNC_ONE)));
    light_mat->set_rasterizer_state(scm::gl::rasterizer_state_desc(scm::gl::FILL_SOLID, scm::gl::CULL_FRONT));
    light_mat->set_depth_stencil_state(scm::gl::depth_stencil_state_desc(false));

    // setup scene
    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "tiles");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(2, 1, 2);

    auto cube_core = new gua::GeometryCore("cube", "tiles_small");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, 0);

    add_monkeys(graph, 10);

    auto lights = add_lights(graph, 256);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 0.5);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);

    gua::RenderServer renderer({create_pipe()});

    gua::Timer timer;
    timer.start();

    double time(0);

    // application loop
    while (true) {
        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        double frame_time(timer.get_elapsed());
        time += frame_time;
        timer.reset();

        for (int i=0; i<lights.size(); ++i) {
            lights[i].translate(0, std::sin(time*(i*0.1 + 0.5))*frame_time*0.5, 0);
        }

        //graph["/box/monkey"].rotate(50*frame_time, 0, 1, 0);
        graph["/screen"].rotate(20*frame_time, 0, 1, 0);
    }

    return 0;
}
