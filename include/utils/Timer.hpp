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
/// \brief Declaration of the Timer class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_TIMER_HPP
#define GUA_TIMER_HPP

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class Timer {

    public:
        void start();
        void reset();

        double get_elapsed() const;

        static double get_now();

    private:
        double start_;

};

}

#endif // GUA_TIMER_HPP





