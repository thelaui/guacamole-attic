 #include "include/guacamole.hpp"

 #include <thread>

 void render(gua::SceneGraph* graph, std::string const& display) {
     gua::Renderer renderer;
     try {
         renderer.add_display(800, 600, display);
         renderer.start_render_loop(graph);
     } catch (std::string& error) {
         std::cerr<<error<<std::endl;
     }
 }

 int main() {
     gua::RenderWindow::init();

     gua::GeometryBase::load_presets();
     gua::MaterialBase::load_presets();

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

     std::thread render_thread(render, &graph, ":0.0");

     while (true) {
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
         graph["/box"].rotate(0.001, 0, 1, 0);
         graph["/box/monkey"].rotate(0.001, 1, 0, 0);
         graph["/box/monkey/monkey"].rotate(0.01, 0, 1, 0);
     }

     return 0;
 }
