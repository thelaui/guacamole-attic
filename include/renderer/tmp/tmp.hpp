#ifndef TMP1_HPP
#define TMP1_HPP

#include <eigen2/Eigen/Geometry>

#include <string>

class GeometryCore {
    public:
        GeometryCore(std::string g, std::string m, Eigen::Transform3f t = (Eigen::Transform3f)Eigen::Transform3f::Identity()):
            geometry_(g), material_(m), transform_(t) {}

        std::string geometry_;
        std::string material_;

        Eigen::Transform3f transform_;
};

class CameraCore {
    public:
        CameraCore(float fovy, float aspect_ratio, float near_plane, float far_plane, Eigen::Transform3f t = (Eigen::Transform3f)Eigen::Transform3f::Identity()):
            projection_(Eigen::Matrix4f::Identity()), transform_(t) {

            const float y_scale = std::tan(M_PI_2 - M_PI/180.f*(fovy / 2));
            const float x_scale = y_scale / aspect_ratio;
            const float frustum_length = far_plane - near_plane;

            projection_[0] = x_scale;
            projection_[5] = y_scale;
            projection_[10] = -((far_plane + near_plane) / frustum_length);
            projection_[11] = -1;
            projection_[14] = -((2 * near_plane * far_plane) / frustum_length);
        }

        Eigen::Matrix4f projection_;
        Eigen::Transform3f transform_;
};

class LightCore {
    public:
        LightCore(Eigen::Transform3f t = (Eigen::Transform3f)Eigen::Transform3f::Identity()):
            transform_(t) {}

        Eigen::Transform3f transform_;
};

#endif //TMP1_HPP
