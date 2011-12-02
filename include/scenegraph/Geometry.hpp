#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "include/scenegraph/Core.hpp"

class Geometry: public Core {
    public:
        Geometry(std::string const& geometry, std::string const& material);
        virtual ~Geometry();

        std::string const& get_geometry() const;
        std::string const& get_material() const;

    private:

};

#endif // GEOMETRY_HPP
