#include "include/guacamole.hpp"

#include <thread>
#include <sstream>

void render(SceneGraph* graph, std::string const& display) {
    Renderer renderer(800, 600, display);
    renderer.start_render_loop(graph);
}

int main() {

    RenderWindow::init();

    GeometryBase::load_presets();
    MaterialBase::load_presets();

    SceneGraph graph;

    auto camera_core = new CameraCore(60.f, 4.f/3.f, 0.1f, 1000.f);
    auto camera = graph.add_node("/", "camera", camera_core);
    camera.translate(0.5, 1, 2);
    camera.rotate(0.2, 0, 1, 0);

    auto cube_core = new GeometryCore("cube", "matt");
    auto floor = graph.add_node("/", "floor", cube_core);
    floor.scale(4, 0.1, 4);

    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(-1, 1, 0);

    auto monkey_core = new GeometryCore("monkey", "shiny");
    auto monkey = graph.add_node("/box", "monkey", monkey_core);
    monkey.translate(0, 2, 0);

    monkey = graph.add_node("/", "monkey", monkey_core);
    monkey.scale(0.3, 0.3, 0.3);
    monkey.translate(4, 1, 0);

    monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
    monkey.scale(0.3, 0.3, 0.3);
    monkey.translate(0, 5, 0);

//    for (int i(0); i < 10; ++i) {
//        std::stringstream papa;
//        papa << "papa" << i;
//        monkey = graph.add_node("/", papa.str(), monkey_core);
//        monkey.translate(0.3*i-2, 1, 0);
//        monkey.scale(0.1, 0.1, 0.1);
//
//        for (int j(0); j < 10; ++j) {
//            std::stringstream child;
//            child << "monk" << j;
//            monkey = graph.add_node("/" + papa.str(), child.str(), monkey_core);
//            monkey.translate(0, j, 0);
//            monkey.scale(0.5, 0.5, 0.5);
//        }
//    }

    for (int i(0); i < 10; ++i) {
        std::stringstream papa;
        papa << "papa" << i;
        monkey = graph.add_node("/", papa.str(), monkey_core);
        monkey.translate(0.3*i-2, 1, 0);
        monkey.scale(0.1, 0.1, 0.1);

        std::string path("/" + papa.str());
        for (int j(0); j < 10; ++j) {
            std::stringstream child;
            child << "monk" << j;
            monkey = graph.add_node(path, child.str(), monkey_core);
            monkey.translate(0, j, 0);
            monkey.scale(0.9, 0.9, 0.9);

            path = path + "/" + child.str();
        }
    }


    //std::cout << graph << std::endl;

    std::thread render_thread1(render, &graph, ":0.0");
    //std::thread render_thread2(render, &graph, ":0.0");

    int frame(0);

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        graph["/box"].rotate(0.001, 0, 1, 0);
        graph["/box/monkey"].rotate(0.001, 1, 0, 0);
        graph["/box/monkey/monkey"].rotate(0.01, 0, 1, 0);

        graph["/monkey"].translate(0, std::sin(0.01*++frame)*0.001, 0);
    }

    return 0;
}
