#include "guacamole.hpp"

#include <thread>

void render(gua::SceneGraph* graph, std::vector<std::pair<const char*, const char*>> windows) {
    gua::Renderer renderer;
    try {
        for (auto& window: windows)
            renderer.add_display(800, 600, window.first, window.second);
        renderer.start_render_loop(graph);
    } catch (std::string& error) {
        std::cerr<<error<<std::endl;
    }
}

int main() {
    gua::RenderWindow::init();

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::MaterialBase::load_materials_from("data/materials/");

    gua::SceneGraph graph;

    auto camera_core = new gua::CameraCore(60.f, 4.f/3.f, 0.1f, 1000.f);
    auto camera = graph.add_node("/", "camera", camera_core);
    camera.translate(0.5, 1, 2);
    camera.rotate(0.2, 0, 1, 0);

    auto cube_core = new gua::GeometryCore("cube", "matt");
    auto floor = graph.add_node("/", "floor", cube_core);
    floor.scale(4, 0.1, 4);

    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(-1, 1, 0);

    auto monkey_core = new gua::GeometryCore("monkey", "shiny");
    auto monkey = graph.add_node("/box", "monkey", monkey_core);
    monkey.translate(0, 2, 0);

    monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
    monkey.scale(0.3, 0.3, 0.3);
    monkey.translate(0, 5, 0);

    camera = graph.add_node("/box", "camera2", camera_core);
    camera.translate(0.5, 1, 4);
    camera.rotate(0.2, 0, 1, 0);

    std::thread render_thread(render, &graph, {std::make_pair("camera2", ":0.0"),
                                               std::make_pair("camera",  ":0.0")});

    gua::DotGenerator dot_generator;
    dot_generator.parse_graph(&graph, "guacamole_scenegraph");
    dot_generator.save_to_file("guacamole_scenegraph.gv");

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        graph["/box"].rotate(0.001, 0, 1, 0);
        graph["/box/monkey"].rotate(0.001, 1, 0, 0);
        graph["/box/monkey/monkey"].rotate(0.01, 0, 1, 0);
    }

    return 0;
}
