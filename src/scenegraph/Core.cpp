#include "include/scenegraph/Core.hpp"

Core::Core(CoreType type):
    type_(type) {}

Core::~Core() {}


Core::CoreType Core::get_type() const {
    return type_;
}
