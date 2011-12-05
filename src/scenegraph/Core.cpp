#include "include/scenegraph/Core.hpp"

Core::Core(CoreType type):
    type_(type),
    transform_(Eigen::Matrix4f::Identity()) {}

Core::~Core() {}


Core::CoreType Core::get_type() const {
    return type_;
}

Eigen::Matrix4f const& Core::get_transform() const {
    return transform_;
}

void Core::set_transform(Eigen::Matrix4f const& transform) {
    transform_ = transform;
}
