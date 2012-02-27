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

    auto plane_core = new gua::GeometryCore("plane", "shiny");
    auto floor = graph.add_node("/", "floor", plane_core);
//    floor.translate(0.04, 0, -2);
//    floor.scale(3.03, 1, 4);
    floor.translate(0, 0.845, -1);
    floor.scale(2.025, 1, 2);

    auto cube_core = new gua::GeometryCore("cube", "shiny");
    auto box = graph.add_node("/", "box", cube_core);
   // box.rotate(-0.5, 0, 1, 0);
    box.translate(0, 0.5+0.845, -1);
    //box.scale(0.5, 0.5, 0.5);
   // box.rotate(M_PI*0.5, 1, 0, 0);

    box = graph.add_node("/", "box2", plane_core);
    box.translate(-0.3, 1.5, 0);
    box.rotate(M_PI*0.5, 1, 0, 0);
    box.scale(1.f, 1.0, 0.5);

//    box = graph.add_node("/", "box2", cube_core);
//    box.scale(0.5, 0.5, 0.5);
//    box.translate(-1, 1, 6);

    auto pivot = graph.add_node("/", "pivot");
    //pivot.translate(0, 0, 0);

    auto screen_core(new gua::ScreenCore(2.025, 1.52));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.845+1.52/2, 0);
//    screen.scale(0.8, 0.6, 1);
//    screen.rotate(0.9, 0, 1, 0);

    auto camera_core = new gua::CameraCore(0.07f, gua::CameraCore::ANAGLYPH_RED_GREEN);
    auto camera = graph.add_node("/", "camera", camera_core);
    camera.translate(3.5, 1.70, 2.5);
//    camera.rotate(M_PI*0.25, 0.f, 1.f, 0.f);

    auto monkey_core = new gua::GeometryCore("cube", "matt");
    auto monkey = graph.add_node("/pivot", "monkey", monkey_core);
    monkey.translate(0.6, 1.6, 1.5);
    monkey.scale(0.05, 0.05, 0.05);
//
//    monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
//    monkey.scale(0.3, 0.3, 0.3);
//    monkey.translate(0, 5, 0);

    setup_lights(graph);

    gua::DotGenerator dot_generator;
    dot_generator.parse_graph(&graph, "guacamole_scenegraph");
    dot_generator.save();

    std::vector<std::vector<std::string>> windows;
    windows.push_back({"camera", "screen", ":0.0"});
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

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
//        graph["/box"].rotate(0.01, 0, 1, 0);
       // graph["/monkey"].rotate(0.01, 1, 0, 0);
//        graph["/box/monkey/monkey"].rotate(0.1, 0, 1, 0);

        graph["/box2"].scale(1, 1, 2);
        graph["/box2"].rotate(-0.005, 0, 0, 1);
        graph["/box2"].scale(1, 1, 0.5);
       graph["/pivot"].rotate(-0.005, 0, 1, 0);
    }

    return 0;
}
