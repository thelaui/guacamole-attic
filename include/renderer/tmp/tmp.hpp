#ifndef TMP1_HPP
#define TMP1_HPP

#include <eigen2/Eigen/Geometry>

#include <string>

class GeometryNode {
    public:
        GeometryNode(std::string const& g, std::string const& m, Eigen::Matrix4f const& t = Eigen::Matrix4f::Identity()):
            geometry_(g), material_(m), transform_(t) {}

        std::string geometry_;
        std::string material_;

        Eigen::Matrix4f transform_;
};

class CameraNode {
    public:
        CameraNode() {};
        CameraNode(Eigen::Matrix4f const& projection, Eigen::Matrix4f const& t = Eigen::Matrix4f::Identity()):
            projection_(projection), transform_(t) {}

        Eigen::Matrix4f projection_;
        Eigen::Matrix4f transform_;
};

class LightNode {
    public:
        LightNode(Eigen::Matrix4f const& t = Eigen::Matrix4f::Identity()):
            transform_(t) {}

        Eigen::Matrix4f transform_;
};

#endif //TMP1_HPP
