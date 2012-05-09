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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Implementation of the profiler class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "utils/Profiler.hpp"

// guacamole headers
#include "utils/debug.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

scm::gl::util::profiling_host_ptr Profiler::
profile_host_ = scm::make_shared<scm::gl::util::profiling_host>();

std::set<std::string> Profiler::
timer_names_;

int Profiler::
interval_ = 500;

int Profiler::
frame_count_ = 0;

////////////////////////////////////////////////////////////////////////////////

Profiler::Timer::
Timer(std::string const& name):
    timer_(*Profiler::profile_host_, name) {

    if (Profiler::profile_host_->enabled())
        Profiler::timer_names_.insert(name);
}

////////////////////////////////////////////////////////////////////////////////

Profiler::Timer::
Timer(std::string const& name, RenderContext const& context):
    timer_(*Profiler::profile_host_, name, context.render_context) {

    if (Profiler::profile_host_->enabled())
        Profiler::timer_names_.insert(name);
}

////////////////////////////////////////////////////////////////////////////////

void Profiler::
enable(bool enable) {

    profile_host_->enabled(enable);
}

////////////////////////////////////////////////////////////////////////////////

void Profiler::
update() {

    profile_host_->update(interval_);
}

////////////////////////////////////////////////////////////////////////////////

void Profiler::
set_interval(int interval) {

    interval_ = interval;
}

////////////////////////////////////////////////////////////////////////////////

void Profiler::
print() {

    if (profile_host_->enabled() && ++frame_count_ > interval_) {

        PROFILING("#### start of profiling information ####");

        for (auto& name: timer_names_) {
            std::cout << name << ": " << scm::gl::util::profiling_result(
                profile_host_, name, scm::time::time_io(
                                                scm::time::time_io::msec, 3))
            << std::endl;
        }

        frame_count_ = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Profiler::
print(std::vector<std::string> const& names) {

    if (profile_host_->enabled() && ++frame_count_ > interval_) {

        PROFILING("#### start of profiling information ####");

        for (auto& name: names) {
            std::cout << name << ": " << scm::gl::util::profiling_result(
                profile_host_, name, scm::time::time_io(
                                                scm::time::time_io::msec, 3))
            << std::endl;
        }

        frame_count_ = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

}





