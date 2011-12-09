#include "include/scenegraph/CameraCore.hpp"

CameraCore::CameraCore(Eigen::Transform3f const& frustum):
    Core(Core::CAMERA),
    frustum_(frustum) {}

CameraCore::~CameraCore() {}

Eigen::Transform3f const& CameraCore::get_frustum() const {
    return frustum_;
}

