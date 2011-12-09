#include "include/scenegraph/SceneGraph.hpp"

#include <iostream>

int main() {
    SceneGraph graph;

    Eigen::Matrix3f transform1;
    transform1 << 1,0,0,
                  0,1,0,
                  0,0,1;

    Eigen::Matrix3f transform2;
    transform2 << 2,0,0,
                  0,2,0,
                  0,0,2;

    Eigen::Matrix3f transform3;
    transform3 << 3,0,0,
                  0,3,0,
                  0,0,3;


    graph.add_node("/", "auto", Eigen::Transform3f(transform1));
    graph.add_node("/auto", "rad1", Eigen::Transform3f(transform2));
    graph.add_node("/auto", "rad2", Eigen::Transform3f(transform3));


    for (auto it(graph.begin()); it != graph.end(); ++it)
        std::cout<<it.transform.matrix()<<std::endl;

    return 0;
}
