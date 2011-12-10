#include "include/scenegraph/SceneGraph.hpp"
#include "include/scenegraph/GeometryCore.hpp"

#include <iostream>

int main() {
    SceneGraph graph;

    graph["/tisch1"];
    //graph.set_working_node("/tisch1");
    graph["bein1"];
    graph["bein2"];
    graph["bein3"];
    graph["bein4"];

   // graph.set_working_node("/");
    graph["/tisch2"];
    graph["/tisch2/bein1"];
    graph["/tisch2/bein2"];
    graph["/tisch2/bein2/schraube1"];
    graph["/tisch2/bein2/schraube2"];
    graph["/tisch2/bein3"];
    graph["/tisch2/bein4"];

    for (SceneGraph::Iterator it(graph.begin()); it!=graph.end(); ++it)
        std::cout<<it.name()<<std::endl;

    graph.remove_node("/tisch2/bein2");

    for (SceneGraph::Iterator it(graph.begin()); it!=graph.end(); ++it)
        std::cout<<it.name()<<std::endl;

    return 0;
}
