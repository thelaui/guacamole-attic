#include "include/scenegraph/SceneGraph.hpp"

#include <iostream>

int main() {
    SceneGraph graph;

    graph.add_node("/", "huhu");
    graph.add_node("/", "haha");
    std::cout<<graph.get_transform("/haha")<<std::endl;
//    graph.add_node("/huhu/", "hoho");
//
//    graph.add_node("/huhu/hoho", "hihi");
//
//    std::cout<<graph.get_relative_transform("/huhu/hoho/hihi", "/huhu")<<std::endl;

    return 0;
}
