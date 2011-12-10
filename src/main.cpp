#include "include/scenegraph/Iterator.hpp"
#include "include/scenegraph/GeometryCore.hpp"

#include <iostream>

int main() {
    SceneGraph graph;

    auto geo_core =std::shared_ptr<GeometryCore>(new GeometryCore("hakaskönni", "holz"));

    graph["/tisch1"] << geo_core << "horst_ole";
    std::cout<<graph["/tisch1"].get_core<GeometryCore>()->get_material()<<std::endl;
    std::cout<<graph["/tisch1"].get_core<GeometryCore>()->get_geometry()<<std::endl;
    std::cout<<graph["/horst_ole"].get_core<GeometryCore>()->get_material()<<std::endl;
    std::cout<<graph["/horst_ole"].get_core<GeometryCore>()->get_geometry()<<std::endl;


    graph["/tisch1/bein1"];
    graph["/tisch1/bein2"];
    graph["/tisch1/bein3"];
    graph["/tisch1/bein4"];

    graph["/tisch2"];
    graph["/tisch2/bein1"];
    graph["/tisch2/bein2"];
    graph["/tisch2/bein2/schraube1"];
    graph["/tisch2/bein2/schraube2"];
    graph["/tisch2/bein3"];
    graph["/tisch2/bein4"].set_name("arm");
    graph["/tisch2/bein4"].set_core(geo_core);

    for (SceneGraph::Iterator it(graph.begin()); it!=graph.end(); ++it) {
        std::cout<<it.get_name()<<std::endl;
    }

    return 0;
}
