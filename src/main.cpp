#include "include/guacamole.hpp"

#include <thread>

//void render(SceneGraph* graph, std::string const& display) {
//    Renderer renderer(800, 600, display);
//    renderer.start_render_loop(*graph);
//}

int main() {
    SceneGraph graph;

    graph.add_node("/", "tisch1");
    graph.add_node("/tisch1", "bein1");
    graph.add_node("/tisch1/bein1", "schraube1");
    graph.add_node("/tisch1/bein1", "schraube2");
    graph.add_node("/tisch1", "bein2");
    graph.add_node("/tisch1", "bein3");
    graph.add_node("/tisch1", "bein4");
    graph.add_node("/", "tisch2");

    graph.move_node("/tisch2", "/tisch3");

    std::cout<<graph<<std::endl;

//    RenderWindow::init();
//
//    GeometryBase::load_presets();
//    MaterialBase::load_presets();
//
//    SceneGraph graph;
//
//    auto camera_core = new CameraCore(60.f, 4.f/3.f, 0.1f, 1000.f);
//    auto camera = graph.add_node("/", "camera", camera_core);
//    camera.translate(0.5, 1, 2);
//    camera.rotate(0.2, 0, 1, 0);
//
//    auto cube_core = new GeometryCore("cube", "matt");
//    auto floor = graph.add_node("/", "floor", cube_core);
//    floor.scale(4, 0.1, 4);
//
//    auto box = graph.add_node("/", "box", cube_core);
//    box.scale(0.5, 0.5, 0.5);
//    box.translate(-1, 1, 0);
//
//    auto monkey_core = new GeometryCore("teapot", "shiny");
//    auto monkey = graph.add_node("/box", "monkey", monkey_core);
//    monkey.translate(0, 2, 0);
//
//    monkey = graph.add_node("/", "monkey", monkey_core);
//    monkey.scale(0.3, 0.3, 0.3);
//    monkey.translate(4, 1, 0);
//
//
//    monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
//    monkey.scale(0.3, 0.3, 0.3);
//    monkey.translate(0, 5, 0);
//
//    std::cout << graph << std::endl;

    //std::thread render_thread1(render, &graph, ":0.0");
    //std::thread render_thread2(render, &graph, ":0.0");

//    int frame(0);
//
//    while (true) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
//        graph["/box"].rotate(0.001, 0, 1, 0);
//        graph["/box/monkey"].rotate(0.001, 1, 0, 0);
//        graph["/box/monkey/monkey"].rotate(0.01, 0, 1, 0);
//
//        graph["/monkey"].translate(0, std::sin(0.01*++frame)*0.001, 0);
//    }

    return 0;
}
