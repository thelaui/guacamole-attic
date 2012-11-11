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

// guacamole headers
#include "traverser/LightNode.hpp"
#include "traverser/GeometryNode.hpp"
#include "traverser/CameraNode.hpp"
#include "traverser/ScreenNode.hpp"

// external headers
#include <vector>
#include <string>
#include <map>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores a serialized scene graph.
///
/// When the optimizer traverses the scene graph, it produces an OptimizedScene
/// which contains relevant nodes only.
////////////////////////////////////////////////////////////////////////////////
struct OptimizedScene {

    ////////////////////////////////////////////////////////////////////////////
    ///\brief All geometry nodes.
    ////////////////////////////////////////////////////////////////////////////
    std::vector<GeometryNode> nodes_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief All light nodes.
    ////////////////////////////////////////////////////////////////////////////
    std::vector<LightNode> lights_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief All cameras.
    ////////////////////////////////////////////////////////////////////////////
    std::map<std::string, CameraNode> cameras_;

    ////////////////////////////////////////////////////////////////////////////
    ///\brief All screens.
    ////////////////////////////////////////////////////////////////////////////
    std::map<std::string, ScreenNode> screens_;
};

}

#endif // GUA_OPTIMIZED_SCENE_HPP

