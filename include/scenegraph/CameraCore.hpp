#ifndef CAMERA_CORE_HPP
#define CAMERA_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <eigen2/Eigen/Geometry>

class CameraCore: public Core {
    public:
        CameraCore(Eigen::Transform3f const& frustum);
        virtual ~CameraCore();

        Eigen::Transform3f const& get_frustum() const;

    private:
        Eigen::Transform3f frustum_;
};

#endif // CAMERA_CORE_HPP
