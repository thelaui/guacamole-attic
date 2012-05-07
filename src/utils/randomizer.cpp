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
/// \brief Implementation of the randomizer utility.
////////////////////////////////////////////////////////////////////////////////

// header
#include "utils/randomizer.hpp"

// external headers
#include <cstdlib>
#include <ctime>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

namespace {

////////////////////////////////////////////////////////////////////////////////

    unsigned int 
    init_seed() {

        unsigned int seed = static_cast<unsigned int>(std::time(NULL));
        std::srand(seed);
        return seed;
    }

    unsigned int global_seed = init_seed();

////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////

void randomizer::
set_seed(unsigned int seed) {

    std::srand(seed);
    global_seed = seed;
}

////////////////////////////////////////////////////////////////////////////////

unsigned int randomizer::
get_seed() {

    return global_seed;
}

////////////////////////////////////////////////////////////////////////////////

float randomizer::
random(float begin, float end) {

    return static_cast<float>(std::rand()) / RAND_MAX * (end - begin) + begin;
}

////////////////////////////////////////////////////////////////////////////////

int randomizer::
random(int begin, int end) {

    return std::rand() % (end - begin + 1) + begin;
}

////////////////////////////////////////////////////////////////////////////////

}
