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
    auto pass = new gua::RenderPass("main", "camera", "screen");
    pass->add_buffer(gua::ColorBufferDescription("color", 0));
    pass->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, "big_scenegraph_example", ":0.0", gua::MONO));
    pipe->add_render_pass(pass);
    pipe->set_final_buffer("main", "color");

    return pipe;
}

std::vector<gua::SceneGraph::Iterator> add_lights(gua::SceneGraph& graph, int count) {

    std::vector<gua::SceneGraph::Iterator> lights(count);

    auto sphere_core = new gua::GeometryCore("light_sphere", "bright");

    for (int i(0); i<count; ++i) {
        auto light_core = new gua::LightCore(gua::Color3f::random());

        scm::math::vec3 randdir(gua::randomizer::random(-1.f, 1.f), gua::randomizer::random(-1.f, 1.f), gua::randomizer::random(-1.f, 1.f));
        scm::math::normalize(randdir);

        lights[i] = graph.add_node("/", "sphere"+gua::string_utils::to_string(i), sphere_core);
        lights[i].scale(0.04, 0.04, 0.04);
        lights[i].translate(randdir[0], randdir[1], randdir[2]);

        auto light = lights[i].add_child("light", light_core);
        light.scale(20, 20, 20);
    }

    return lights;
}

void setup_scene(gua::SceneGraph& graph, gua::SceneGraph::Iterator& root_monkey,
                 int depth_count) {
    if (depth_count > 0) {
        auto ape = root_monkey.add_child("monkey1", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(0, 1, 0);

        setup_scene(graph, ape, depth_count-1);

        ape = root_monkey.add_child("monkey2", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(1, 0, 0);

        setup_scene(graph, ape, depth_count-1);

        ape = root_monkey.add_child("monkey3", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(0, -1, 0);

        setup_scene(graph, ape, depth_count-1);

        ape = root_monkey.add_child("monkey4", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(-1, 0, 0);

        setup_scene(graph, ape, depth_count-1);

        ape = root_monkey.add_child("monkey5", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(0, 0, 1);

        setup_scene(graph, ape, depth_count-1);

        ape = root_monkey.add_child("monkey6", root_monkey.get_core());
        ape.scale(0.5, 0.5, 0.5);
        ape.translate(0, 0, -1);

        setup_scene(graph, ape, depth_count-1);
    }
}

int main(int argc, char** argv) {

    // initialize guacamole
    gua::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

   // gua::Profiler::enable(true);

    // setup scene
    gua::SceneGraph graph;

    auto monkey_core = new gua::GeometryCore("cube", "wood");
    auto root_monkey = graph.add_node("/", "root_ape", monkey_core);
    root_monkey.scale(0.5, 0.5, 0.5);

    // depth    monkey    cube          car
    // 1        14.084      56    3.619.000 Vertices  /      7 draw calls
    // 2        74.444     296   19.129.000 Vertices  /     37 draw calls
    // 3       436.604   1.736  112.189.000 Vertices  /    217 draw calls
    // 4     2.609.564  10.376              Vertices  /  1.297 draw calls
    // 5    15.647.324  62.216              Vertices  /  7.777 draw calls
    setup_scene(graph, root_monkey, 4);

    auto lights = add_lights(graph, 56);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0, 1.f);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);

    gua::RenderServer renderer({create_pipe()});


    gua::DotGenerator generator;
    generator.parse_graph(&graph, "big_graph");
    generator.save("/home/rufu1194/");

    gua::Timer timer;
    timer.start();

    double time(0);

    // application loop
    while (true) {
        double frame_time(timer.get_elapsed());
        time += frame_time;
        timer.reset();

        for (auto it(graph.begin()); it != graph.end(); ++it) {
            if (it.get_core() && it.get_core()->get_type() == gua::Core::GEOMETRY)
                it.rotate(frame_time*3, 1, 1, 0);
        }

        for (int i=0; i<lights.size(); ++i) {
            lights[i].rotate(std::sin(time*(i*0.1 + 0.5))*frame_time*0.5, 0, 1, 0);
        }

        graph["/root_ape"].rotate(15*frame_time, 0, 1, 0);
        graph["/screen"].rotate(20*frame_time, 0, 1, 0);

        renderer.queue_draw(&graph);
    }

    return 0;
}
