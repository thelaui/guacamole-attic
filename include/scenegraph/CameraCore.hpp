#ifndef CAMERA_CORE_HPP
#define CAMERA_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <eigen2/Eigen/Geometry>

class CameraCore: public Core {
    public:
        CameraCore(float fovy, float aspect_ratio, float near_plane, float far_plane);
        virtual ~CameraCore();

        Eigen::Matrix4f const& get_frustum() const;

    private:
        Eigen::Matrix4f frustum_;
};

#endif // CAMERA_CORE_HPP
