#ifndef GEOMETRY_CORE_HPP
#define GEOMETRY_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <string>

class GeometryCore: public Core {
    public:
        GeometryCore(std::string const& geometry, std::string const& material);
        virtual ~GeometryCore();

        std::string const& get_geometry() const;
        std::string const& get_material() const;

    private:
        std::string geometry_, material_;

};

#endif // GEOMETRY_CORE_HPP
