//#include "include/scenegraph/Iterator.hpp"
//#include "include/scenegraph/GeometryCore.hpp"
//
//#include <iostream>
//
//int main() {
//    SceneGraph graph;
//
//    auto geo_core =std::shared_ptr<GeometryCore>(new GeometryCore("hakaskönni", "holz"));
//
//    graph["/tisch1"] << geo_core << "horst_ole";
//    std::cout<<graph["/tisch1"].get_core<GeometryCore>()->get_material()<<std::endl;
//    std::cout<<graph["/tisch1"].get_core<GeometryCore>()->get_geometry()<<std::endl;
//    std::cout<<graph["/horst_ole"].get_core<GeometryCore>()->get_material()<<std::endl;
//    std::cout<<graph["/horst_ole"].get_core<GeometryCore>()->get_geometry()<<std::endl;
//
//
//    graph["/tisch1/bein1"];
//    graph["/tisch1/bein2"];
//    graph["/tisch1/bein3"];
//    graph["/tisch1/bein4"];
//
//    graph["/tisch2"];
//    graph["/tisch2/bein1"];
//    graph["/tisch2/bein2"];
//    graph["/tisch2/bein2/schraube1"];
//    graph["/tisch2/bein2/schraube2"];
//    graph["/tisch2/bein3"];
//    graph["/tisch2/bein4"].set_name("arm");
//    graph["/tisch2/bein4"].set_core(geo_core);
//
//    for (SceneGraph::Iterator it(graph.begin()); it!=graph.end(); ++it) {
//        std::cout<<it.get_name()<<std::endl;
//    }
#include "include/renderer/MaterialBase.hpp"
#include "include/utils/debug.hpp"

#include "include/utils/debug.hpp"

#include <eigen2/Eigen/Geometry>

#include "include/renderer/GeometryBase.hpp"
#include "include/renderer/MaterialBase.hpp"
#include "include/renderer/RenderBackend.hpp"
#include "include/renderer/tmp/tmp.hpp"

#include <thread>

void thread() {
    RenderBackend renderer(800, 600, ":0.0");

    GeometryCore ape1("teapot", "shiny");
    ape1.transform_.translate(Eigen::Vector3f(-2, 0, 0));

    GeometryCore ape2("ape", "matt");
    ape2.transform_.translate(Eigen::Vector3f(2, 0, 0));
    ape2.transform_.scale(1.3);

    CameraCore cam(60.f, 4.f/3.f, 0.1f, 1000.f);
    cam.transform_.translate(Eigen::Vector3f(0, 0, 4));

    while (true) {
        ape1.transform_.rotate(Eigen::AngleAxisf(0.01, Eigen::Vector3f(0, 1, 0)));
        ape2.transform_.rotate(Eigen::AngleAxisf(-0.01, Eigen::Vector3f(0, 1, 0)));

        renderer.render({&ape1, &ape2}, {}, cam);
    }
}

int main() {
    GeometryBase::load_presets();
    MaterialBase::load_presets();

    RenderWindow::init();

    std::thread thread1(&thread);
    //std::thread thread2(&thread);

    thread1.join();
    //thread2.join();

    return 0;
}
