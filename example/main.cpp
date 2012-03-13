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
    gua::TextureBase::load_textures_from("data/textures/");
    gua::MaterialBase::load_materials_from("data/materials/");

    gua::SceneGraph graph;

    auto plane_core = new gua::GeometryCore("plane", "tiles");
    auto floor = graph.add_node("/", "floor", plane_core);
    floor.scale(1.6, 1, 2);

    auto cube_core = new gua::GeometryCore("cube", "tiles_small");
    auto box = graph.add_node("/", "box", cube_core);
    box.scale(0.2, 0.2, 0.2);
    box.translate(0, 0.1, 0);

    auto monkey_core = new gua::GeometryCore("monkey", "wood");
    box = graph.add_node("/box", "box", monkey_core);
    box.scale(0.5, 0.5, 0.5);
    box.translate(0, 1, 0);

    auto screen_core(new gua::ScreenCore(1.6, 0.9));
    auto screen = graph.add_node("/", "screen", screen_core);
    screen.translate(0, 0.45, 0.5);

    screen = graph.add_node("/", "mirror_screen", screen_core);
    screen.translate(0, -0.45, 0.5);

    auto camera_core = new gua::CameraCore(0.1f);
    auto camera = graph.add_node("/screen", "camera", camera_core);
    camera.translate(0, 0, 1.5);

    camera = graph.add_node("/mirror_screen", "mirror_camera", camera_core);
    camera.translate(0, 0, 1.5);

    setup_lights(graph);


    auto mirror_pass = new gua::RenderPass("mirror", "camera", "screen", "/", 0.2, 0.2);
    mirror_pass->add_buffer(gua::RenderPass::ColorBufferDescription("color", 0));
    mirror_pass->add_buffer(gua::RenderPass::ColorBufferDescription("normal", 1));
    mirror_pass->add_buffer(gua::RenderPass::ColorBufferDescription("texcoord", 2));
    mirror_pass->add_buffer(gua::RenderPass::DepthStencilBufferDescription("depth_stencil"));

    auto pass = new gua::RenderPass("simple", "camera", "screen", "/");
    pass->add_buffer(gua::RenderPass::ColorBufferDescription("color", 0));
    pass->add_buffer(gua::RenderPass::ColorBufferDescription("normal", 1));
    pass->add_buffer(gua::RenderPass::ColorBufferDescription("texcoord", 2));
    pass->add_buffer(gua::RenderPass::DepthStencilBufferDescription("depth_stencil"));
    pass->set_input_buffer("mirror", "normal", "tiles_small", "tex");

    auto pipe = new gua::RenderPipeline(gua::RenderWindow::Description(1600, 900, ":0.0"), gua::RenderPipeline::MONO);
    pipe->add_render_pass(mirror_pass);
    pipe->add_render_pass(pass);
    pipe->set_final_buffer("simple", "color");

    std::vector<gua::RenderPipeline*> pipelines;
    pipelines.push_back(pipe);

    gua::RenderServer renderer(pipelines);

    int frame(0);
    while (true) {
        renderer.queue_draw(&graph);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        ++frame;
        graph["/box"].translate((std::sin(frame*0.01))*0.001, 0, 0);
        graph["/box/box"].rotate(0.02, 0, 1, 0);
        graph["/screen"].rotate(0.001, 0, 1, 0);
        graph["/mirror_screen"].rotate(0.001, 0, 1, 0);
    }

    return 0;
}
