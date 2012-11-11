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
#include <scm/input/tracking/art_dtrack.h>
#include <scm/input/tracking/target.h>

gua::RenderPipeline* create_pipe(std::string const& camera, std::string const& screen, std::string const& display) {
    // setup rendering pipeline
    auto pass = new gua::RenderPass("main", camera, screen);
    pass->add_buffer(gua::ColorBufferDescription("color", 0));
    pass->add_buffer(gua::DepthStencilBufferDescription("depth_stencil"));

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 600, "tracking_example", display, gua::SIDE_BY_SIDE, "/opt/dlp-warpmatrices/"));
    pipe->add_render_pass(pass);
    pipe->set_final_buffer("main", "color");

    return pipe;
}

int main(int argc, char** argv) {
    // initialize guacamole
    gua::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

    scm::inp::art_dtrack* dtrack(new scm::inp::art_dtrack(5002));

    if (!dtrack->initialize()) {
        return -1;
    }

    scm::inp::tracker::target_container targets;
    targets.insert(scm::inp::tracker::target_container::value_type(1, scm::inp::target(1)));
    targets.insert(scm::inp::tracker::target_container::value_type(2, scm::inp::target(2)));
    targets.insert(scm::inp::tracker::target_container::value_type(3, scm::inp::target(3)));
    targets.insert(scm::inp::tracker::target_container::value_type(4, scm::inp::target(4)));
    targets.insert(scm::inp::tracker::target_container::value_type(5, scm::inp::target(5)));
    targets.insert(scm::inp::tracker::target_container::value_type(6, scm::inp::target(6)));

    // setup scene
    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "tiles");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(5, 1, 5);

    auto cube_core = new gua::GeometryCore("cube", "tiles_small");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(0, 0.25, 0);

    auto monkey_core = new gua::GeometryCore("monkey", "wood");
    auto ape = graph.add_node("/box", "monkey", monkey_core);
    ape.scale(0.5, 0.5, 0.5);
    ape.translate(0, 1, 0);

    auto screen_core(new gua::ScreenCore(4.18f, 2.58f));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 1.57, 1.5);

    auto camera_core = new gua::CameraCore(0.065f);
    graph.add_node("/screen", "camera1", camera_core);
    graph.add_node("/screen", "camera2", camera_core);
    graph.add_node("/screen", "camera3", camera_core);
    graph.add_node("/screen", "camera4", camera_core);
    graph.add_node("/screen", "camera5", camera_core);
    graph.add_node("/screen", "camera6", camera_core);

    gua::RenderServer renderer({create_pipe("camera1", "screen", ":0.0")/*, create_pipe("camera2", "screen", ":0.1"),
                                create_pipe("camera3", "screen", ":0.2"), create_pipe("camera4", "screen", ":0.3"),
                                create_pipe("camera5", "screen", ":0.4"), create_pipe("camera6", "screen", ":0.5")*/});

    // application loop
    while (true) {
        dtrack->update(targets);

	    // head target
	    for (unsigned i(0); i < targets.size(); ++i) {
            auto target_it = targets.find(i+1);
            if (target_it != targets.end()) {
                auto transform(target_it->second.transform());
                transform[12] /= 1000.f;
                transform[13] /= 1000.f;
                transform[14] /= 1000.f;
                transform = scm::math::make_translation(0.f, -1.57f, 2.f) * transform;
                graph["/screen/camera" + gua::string_utils::to_string<int>(i+1)].set_transform(transform);
            }
        }


        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        graph["/box/monkey"].rotate(2, 0, 1, 0);
    }

    return 0;
}
