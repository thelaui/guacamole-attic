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
/// \brief Declaration of the profiler class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_PROFILER_HPP
#define GUA_PROFILER_HPP

// guacamole headers
#include "renderer/RenderContext.hpp"

// external headers
#include <scm/core/time/accum_timer.h>
#include <scm/gl_util/utilities.h>
#include <string>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief
///
///
////////////////////////////////////////////////////////////////////////////////
class Profiler {
    public:

        class Timer {
            public:
                Timer(std::string const& name);
                Timer(std::string const& name, RenderContext const& context);

            private:
                scm::gl::util::scoped_timer timer_;
        };

        static void enable(bool enable);

        static void set_interval(int interval);

        static void update();

        static void print_all();
        static void print_specific(std::vector<std::string> const& names);

        friend class Timer;

    private:
        static scm::gl::util::profiling_host_ptr profile_host_;
        static std::set<std::string> timer_names_;

        static int interval_;
        static int frame_count_;
};

}
# endif // GUA_PROFILER_HPP




