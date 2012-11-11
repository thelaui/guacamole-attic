////////////////////////////////////////////////////////////////////////////////
// Guacamole - An interesting scenegraph implementation.
//
// Copyright: (c) 2011-2012 by Felix Lauer and Simon Schneegans
// Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de
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
/// \brief A singleton base class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_SINGLETON_HPP
#define GUA_SINGLETON_HPP

#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
/// \brief This is base class for singletons.
///
/// Singletons are classes, which are only instanciated once.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

template <typename T>

class Singleton {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the instance.
        ///
        /// Singletons are classes, which are only instanciated once. This
        /// method will create this instance if necessary and return a pointer
        /// to it.
        ///
        /// \return The instance of this singleton.
        ////////////////////////////////////////////////////////////////////////
        static T* instance() {
            if (instance_ == NULL)
                instance_ = new T;

            return instance_;
        };

        ////////////////////////////////////////////////////////////////////////
        /// \brief Deletes the instance of this Singleton.
        ///
        /// The instance of this singleton will be deleted by this method.
        ////////////////////////////////////////////////////////////////////////
        static void destroy_instance() {
            if (instance_ != NULL) {
                delete instance_;
                instance_ = NULL;
            }
        };

    protected:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Has to be private in derived classe.
        ////////////////////////////////////////////////////////////////////////
        Singleton() {};

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Has to be private in derived classe.
        ////////////////////////////////////////////////////////////////////////
        virtual ~Singleton() {};

    private:
        Singleton(Singleton const& copy) {};

        static T* instance_;

};

template <typename T> T* Singleton<T>::instance_ = NULL;

}

#endif //SINGLETON_HPP

