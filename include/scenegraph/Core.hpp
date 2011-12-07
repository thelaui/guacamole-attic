#ifndef CORE_HPP
#define CORE_HPP

class Core {
    public:
        enum CoreType { CAMERA, GEOMETRY, LIGHT };

        Core(CoreType type);
        virtual ~Core();

        CoreType get_type() const;

    private:
        CoreType type_;

};

#endif // CORE_HPP
