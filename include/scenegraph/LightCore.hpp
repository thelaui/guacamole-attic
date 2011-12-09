#ifndef LIGHT_CORE_HPP
#define LIGHT_CORE_HPP

#include "include/scenegraph/Core.hpp"

#include <string>

class LightCore: public Core {
    public:
        LightCore(std::string const& color);
        virtual ~LightCore();

        std::string const& get_color() const;

    private:
        std::string color_;

};

#endif // LIGHT_CORE_HPP
