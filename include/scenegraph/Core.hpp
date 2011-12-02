#ifndef CORE_HPP
#define CORE_HPP

class Core {
    public:
        enum CoreType { CAMERA, GEOMETRY, LIGHT };

        Core();
        virtual ~Core();

        CoreType get_type() const;
        Eigen::Matrix4f const& get_transform() const;

    private:

};

#endif // CORE_HPP
