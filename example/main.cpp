#include "guacamole.hpp"

#include <thread>


void setup_lights(gua::SceneGraph& graph) {

    auto point_light_core1 = new gua::LightCore(gua::Color3f(1.f, 1.f, 0.f));
    auto point_light_core2 = new gua::LightCore(gua::Color3f(1.f, 0.f, 1.f));
    auto point_light_core3 = new gua::LightCore(gua::Color3f(1.f, 1.f, 0.f));
    auto point_light_core4 = new gua::LightCore(gua::Color3f(0.f, 1.f, 1.f));

//    auto point_light_core1 = new gua::LightCore(gua::Color3f(0.6f, 0.6f, 0.6f));
//    auto point_light_core2 = new gua::LightCore(gua::Color3f(0.6f, 0.6f, 0.6f));
//    auto point_light_core3 = new gua::LightCore(gua::Color3f(0.6f, 0.6f, 0.6f));
//    auto point_light_core4 = new gua::LightCore(gua::Color3f(0.6f, 0.6f, 0.6f));

    auto point_light1 = graph.add_node("/", "point_light1", point_light_core1);
    auto point_light2 = graph.add_node("/", "point_light2", point_light_core2);
    auto point_light3 = graph.add_node("/", "point_light3", point_light_core3);
    auto point_light4 = graph.add_node("/", "point_light4", point_light_core4);

    point_light1.translate(2.f, 2.5f, -2.f);
    point_light2.translate(2.f, 2.5f, 2.f);
    point_light3.translate(-2.f,2.5f, 2.f);
    point_light4.translate(-2.f, 2.5f, -2.f);

    point_light1.scale(15.f, 15.f, 15.f);
    point_light2.scale(15.f, 15.f, 15.f);
    point_light3.scale(15.f, 15.f, 15.f);
    point_light4.scale(15.f, 15.f, 15.f);
}

int main() {
    gua::RenderWindow::init();

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::MaterialBase::load_materials_from("data/materials/");

    gua::SceneGraph graph;

    auto cube_core = new gua::GeometryCore("cube", "shiny");
    auto floor = graph.add_node("/", "floor", cube_core);
    floor.scale(4, 0.1, 4);

    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(-1, 1, 0);

    box = graph.add_node("/", "box2", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(-1, 1, 6);

    graph.add_node("/", "pivot");

    auto camera_core = new gua::CameraCore(60.f, 16.f/9.f, 0.1f, 1000.f, 0.2f, gua::CameraCore::MONO);
    auto camera = graph.add_node("/pivot", "camera", camera_core);
    camera.translate(0, 2, 4);
    camera.rotate(-0.4, 1, 0, 0);

    auto monkey_core = new gua::GeometryCore("monkey", "matt");
    auto monkey = graph.add_node("/box", "monkey", monkey_core);
    monkey.translate(0, 2, 0);

    monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
    monkey.scale(0.3, 0.3, 0.3);
    monkey.translate(0, 5, 0);

    setup_lights(graph);

    gua::DotGenerator dot_generator;
    dot_generator.parse_graph(&graph, "guacamole_scenegraph");
    dot_generator.save();

    std::vector<std::pair<std::string, std::string>> windows;
    windows.push_back(std::make_pair("camera", ":0.0"));
    gua::Renderer renderer(windows);

    gua::Timer timer;
    timer.start();

    int frame(0);
    while (true) {
        if (++frame % 100 == 0) {
            WARNING("Application FPS: %f", frame/timer.get_elapsed());
            frame = 0;
            timer.reset();
        }

        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        graph["/box"].rotate(0.01, 0, 1, 0);
        graph["/box/monkey"].rotate(0.01, 1, 0, 0);
        graph["/box/monkey/monkey"].rotate(0.1, 0, 1, 0);

        graph["/pivot"].rotate(-0.005, 0, 1, 0);
    }

    return 0;
}
