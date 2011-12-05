#ifndef CORE_HPP
#define CORE_HPP

#include <eigen2/Eigen/Eigen>

class Core {
    public:
        enum CoreType { CAMERA, GEOMETRY, LIGHT };

        Core(CoreType type);
        virtual ~Core();

        CoreType get_type() const;
        Eigen::Matrix4f const& get_transform() const;

        void set_transform(Eigen::Matrix4f const& transform);

    private:
        CoreType type_;
        Eigen::Matrix4f transform_;

};

#endif // CORE_HPP
