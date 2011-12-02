#ifndef KNOWN_OBJECT_HPP
#define KNOWN_OBJECT_HPP

#include <cstddef>
#include <vector>

template <typename T>

class KnownObject {
    public:
        KnownObject():
            object_id_(existing_objects_.size()) {

            existing_objects_.push_back(reinterpret_cast<T*>(this));
        }

        virtual ~KnownObject() {
            existing_objects_[object_id_] = NULL;
        }

        static T* pointer(int index = existingObjects_.size()-1) {
            if (index >= 0 && index < existingObjects_.size())
                return existingObjects_[index];
            return NULL;
        }

    protected:
        const int object_id_;

    private:
        static std::vector<T*> existing_objects_;

};


template <typename T>
std::vector<T*> KnownObject<T>::existing_objects_;

#endif //KNOWN_OBJECT_HPP
