#include "guacamole.hpp"

#include <thread>


void setup_lights(gua::SceneGraph& graph) {
    auto point_light_core1 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core2 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core3 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));
    auto point_light_core4 = new gua::LightCore(gua::Color3f(0.99f, 0.99f, 0.99f));

    auto point_light1 = graph.add_node("/", "point_light1", point_light_core1);
    auto point_light2 = graph.add_node("/", "point_light2", point_light_core2);
    auto point_light3 = graph.add_node("/", "point_light3", point_light_core3);
    auto point_light4 = graph.add_node("/", "point_light4", point_light_core4);

    point_light1.scale(3.f, 3.f, 3.f);
    point_light2.scale(3.f, 3.f, 3.f);
    point_light3.scale(3.f, 3.f, 3.f);
    point_light4.scale(3.f, 3.f, 3.f);

    point_light1.translate(0.5f, 0.5f, -0.5f);
    point_light2.translate(0.5f, 0.5f, 0.5f);
    point_light3.translate(-0.5f, 0.5f, 0.5f);
    point_light4.translate(-0.5f, 0.5f, -0.5f);
}

int main() {
    gua::init();

    gua::GeometryBase::load_objects_from("data/objects/");
    gua::MaterialBase::load_materials_from("data/materials/");
    gua::TextureBase::load_textures_from("data/textures/");

    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "shiny");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(1.6, 1, 2);
    floor.translate(0, 0, -1);

    auto cube_core = new gua::GeometryCore("cube", "shiny");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, -0.1);

    box = graph.add_node("/box", "box", cube_core);
    box.scale(0.5, 0.5, 0.5);
    box.rotate(M_PI*0.5, 0, 0, 1, gua::SceneGraph::GLOBAL, gua::SceneGraph::PRIVATE);
    box.translate(0, 0.75, 0);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 0);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0.45, 3.5);

    setup_lights(graph);

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, ":0.0"), gua::RenderPipeline::MONO);
    auto pass = new gua::RenderPass("simple", "camera", "screen", "/");

    pass->add_color_buffer("color", 0);
    pass->add_depth_stencil_buffer("depth_stencil");

    pipe->add_render_pass(pass);
    pipe->set_final_buffer("simple", "color");

    std::vector<gua::RenderPipeline*> pipelines;
    pipelines.push_back(pipe);

    gua::RenderServer renderer(pipelines);

    while (true) {
        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        graph["/box"].rotate(0.02, 0, 1, 0, gua::SceneGraph::LOCAL, gua::SceneGraph::PUBLIC);
    }

    return 0;
}
