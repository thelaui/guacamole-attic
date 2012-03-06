#include "guacamole.hpp"

#include <thread>


void setup_lights(gua::SceneGraph& graph) {

//    auto point_light_core1 = new gua::LightCore(gua::Color3f(1.f, 1.f, 0.f));
//    auto point_light_core2 = new gua::LightCore(gua::Color3f(1.f, 0.f, 1.f));
//    auto point_light_core3 = new gua::LightCore(gua::Color3f(1.f, 1.f, 0.f));
//    auto point_light_core4 = new gua::LightCore(gua::Color3f(0.f, 1.f, 1.f));

    auto point_light_core1 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core2 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core3 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core4 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));

    auto point_light1 = graph.add_node("/", "point_light1", point_light_core1);
    auto point_light2 = graph.add_node("/", "point_light2", point_light_core2);
    auto point_light3 = graph.add_node("/", "point_light3", point_light_core3);
    auto point_light4 = graph.add_node("/", "point_light4", point_light_core4);

    point_light1.scale(4.f, 4.f, 4.f);
    point_light2.scale(4.f, 4.f, 4.f);
    point_light3.scale(4.f, 4.f, 4.f);
    point_light4.scale(4.f, 4.f, 4.f);

    point_light1.translate(0.5f, 0.2f, -1.f);
    point_light2.translate(0.5f, 0.2f, 1.f);
    point_light3.translate(-0.5f,0.2f, 1.f);
    point_light4.translate(-0.5f, 0.2f, -1.f);
}

int main(int argc, char** argv) {
    gua::RenderWindow::init(argc, argv);

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::MaterialBase::load_materials_from("data/materials/");

    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "shiny");
    auto floor = graph.add_node("/", "floor", plane_core);
//    floor.translate(0.04, 0, -2);
//    floor.scale(3.03, 1, 4);
    floor.scale(1.6, 1, 2);
    floor.translate(0, 0, -1);

    auto cube_core = new gua::GeometryCore("cube", "shiny");
    auto box = graph.add_node("/", "box", cube_core);
   // box.rotate(-0.5, 0, 1, 0);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, -0.1);

    box = graph.add_node("/box", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.rotate(90, 0, 0, 1, gua::SceneGraph::GLOBAL, gua::SceneGraph::PRIVATE);
    box.translate(0, 0.75, 0);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
   // screen.scale(1.6, 0.9, 1);
//    screen.rotate(0.4, 0, 1, 0);
    screen.translate(0, 0.45, 0);

    auto camera_core = new gua::CameraCore(0.1f, gua::CameraCore::MONO);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0.45, 3.5);
    //camera.scale(0.5, 0.5, 0.5);
   // camera.rotate(M_PI, 0.f, 1.f, 0.f);

    setup_lights(graph);
//
//    gua::DotGenerator dot_generator;
//    dot_generator.parse_graph(&graph, "guacamole_scenegraph");
//    dot_generator.save();

    std::vector<std::vector<std::string>> windows;
    windows.push_back({"camera", "screen", ":0.0"});
    gua::Renderer renderer(windows);

    gua::Timer timer;
    timer.start();

    int frame(0);
    while (true) {
        if (++frame % 100 == 0) {
            //WARNING("Application FPS: %f", frame/timer.get_elapsed());
            frame = 0;
            timer.reset();
        }

        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        graph["/box"].rotate(1, 0, 0, 1, gua::SceneGraph::GLOBAL, gua::SceneGraph::PRIVATE);
        graph["/box"].rotate(0.7, 0, 1, 0, gua::SceneGraph::LOCAL, gua::SceneGraph::PUBLIC);
    }

    return 0;
}
