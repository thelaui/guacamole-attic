////////////////////////////////////////////////////////////////////////////////
// guacamole - an interesting scenegraph implementation
//
// Copyright (c) 2011 by Mischa Krempel, Felix Lauer and Simon Schneegans
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the KnownObject class.
////////////////////////////////////////////////////////////////////////////////

#ifndef KNOWN_OBJECT_HPP
#define KNOWN_OBJECT_HPP

#include <cstddef>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class may be used to create globally known objects without
///        having to implement them as singletons.
///
/// Objects of classes which are derived from this class automatically are
/// stored in a static vector. A static function allows to get a pointer on each
/// of the generated objects.
///
/// NOTE: This class is NOT ment for objects created in a really big amount!
////////////////////////////////////////////////////////////////////////////////

template <typename T>

class KnownObject {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a KnownObject and stores a pointer on an object
        /// of a derived class into a static list.
        ////////////////////////////////////////////////////////////////////////
        KnownObject():
            object_id_(existing_objects_.size()) {

            existing_objects_.push_back(reinterpret_cast<T*>(this));
        }

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This destructs a KnownObject frees the storage the deleted object
        /// used to allocate in the static vector
        ////////////////////////////////////////////////////////////////////////
        virtual ~KnownObject() {
            existing_objects_[object_id_] = NULL;
        }

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns a pointer on a derived object.
        ///
        /// This function returns a pointer on any of the already constructed
        /// derived objects.
        ///
        ///\param index   The position of the wanted object in the static vector.
        ///
        ///\return object The object of the derived class
        ////////////////////////////////////////////////////////////////////////
        static T* pointer(unsigned index = existing_objects_.size()-1) {
            if (index >= 0 && index < existing_objects_.size())
                return existing_objects_[index];
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
