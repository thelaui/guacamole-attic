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
/// \brief A singleton base class.
////////////////////////////////////////////////////////////////////////////////

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <cstddef>

template <typename T>

class Singleton {
    public:
        static T* instance() {
            if (instance_ == NULL)
                instance_ = new T;

            return instance_;
        };

        static void destroy_instance() {
            if (instance_ != NULL) {
                delete instance_;
                instance_ = NULL;
            }
        };

    protected:
        Singleton() {};
        virtual ~Singleton() {};

    private:
        Singleton(Singleton const& copy) {};

        static T* instance_;

};

template <typename T> T* Singleton<T>::instance_ = NULL;

#endif //SINGLETON_HPP

