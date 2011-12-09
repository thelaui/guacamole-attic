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
    graph.add_node("/auto/rad1", "felge1", Eigen::Transform3f(transform3));
    graph.add_node("/auto/rad1", "felge2", Eigen::Transform3f(transform3));
    graph.add_node("/auto/rad2", "felge3", Eigen::Transform3f(transform3));
    graph.add_node("/auto/rad2", "felge4", Eigen::Transform3f(transform3));
    graph.add_node("/auto/rad2/felge4", "speiche1", Eigen::Transform3f(transform3));

    graph.add_node("/", "auto2", Eigen::Transform3f(transform1));
    graph.add_node("/auto2", "rad1", Eigen::Transform3f(transform2));
    graph.add_node("/auto2", "rad2", Eigen::Transform3f(transform3));
    graph.add_node("/auto2/rad1", "felge1", Eigen::Transform3f(transform3));
    graph.add_node("/auto2/rad1", "felge2", Eigen::Transform3f(transform3));
    graph.add_node("/auto2/rad2", "felge3", Eigen::Transform3f(transform3));


    for (auto it(graph.begin()); it != graph.end(); ++it) {

        std::cout<<it.name<<std::endl;
        std::cout<<it.depth<<std::endl;
    }

    return 0;
}
