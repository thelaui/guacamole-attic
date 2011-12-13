#include "include/scenegraph/CameraCore.hpp"

CameraCore::CameraCore(float fovy, float aspect_ratio, float near_plane, float far_plane):
    Core(Core::CAMERA),
    frustum_(Eigen::Matrix4f::Identity()) {

    const float y_scale = std::tan(M_PI_2 - M_PI/180.f*(fovy / 2));
    const float x_scale = y_scale / aspect_ratio;
    const float frustum_length = far_plane - near_plane;

    frustum_[0] = x_scale;
    frustum_[5] = y_scale;
    frustum_[10] = -((far_plane + near_plane) / frustum_length);
    frustum_[11] = -1;
    frustum_[14] = -((2 * near_plane * far_plane) / frustum_length);
}

CameraCore::~CameraCore() {}

Eigen::Matrix4f const& CameraCore::get_frustum() const {
    return frustum_;
}

