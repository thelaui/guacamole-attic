#include "include/scenegraph/GeometryCore.hpp"

GeometryCore::GeometryCore(std::string const& geometry, std::string const& material):
    Core(Core::GEOMETRY),
    geometry_(geometry),
    material_(material) {}

GeometryCore::~GeometryCore() {}

std::string const& GeometryCore::get_geometry() const {
    return geometry_;
}

std::string const& GeometryCore::get_material() const {
    return material_;
}
