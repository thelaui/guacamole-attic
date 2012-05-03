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
/// \brief Implementation of the Timer class.
////////////////////////////////////////////////////////////////////////////////

#include "utils/Timer.hpp"

#include <thread>

namespace gua {

void Timer::start() {
    start_ = get_now();
}

void Timer::reset() {
    start_ = get_now();
}

double Timer::get_elapsed() const {
    return get_now() - start_;
}

double Timer::get_now() {
    auto time = std::chrono::system_clock::now();
    auto since_epoch = time.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch).count()*0.001;
}

}




