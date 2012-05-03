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
/// \brief Declaration of the OptimizedScene struct.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_OPTIMIZED_SCENE_HPP
#define GUA_OPTIMIZED_SCENE_HPP

#include <vector>
#include <string>
#include <map>

#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"
#include "traverser/ScreenNode.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a light for rendering.
///
////////////////////////////////////////////////////////////////////////////////
struct OptimizedScene {

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    std::vector<GeometryNode> nodes_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    std::vector<LightNode> lights_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    std::map<std::string, CameraNode> cameras_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief Destructor.
    ///
    /// This destroys an Optimizer.
    ////////////////////////////////////////////////////////////////////////////
    std::map<std::string, ScreenNode> screens_;
};

}

#endif // GUA_OPTIMIZED_SCENE_HPP

