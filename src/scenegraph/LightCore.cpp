#include "include/scenegraph/LightCore.hpp"

LightCore::LightCore(std::string const& color):
    Core(Core::LIGHT),
    color_(color) {}

LightCore::~LightCore() {}

std::string const& LightCore::get_color() const {
    return color_;
}


