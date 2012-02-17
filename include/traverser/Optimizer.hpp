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
/// \brief Declaration of the Optimizer class.
////////////////////////////////////////////////////////////////////////////////

#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include <vector>
#include <memory>
#include <map>

#include "traverser/OptimizedScene.hpp"

namespace gua {

class GeometryNode;
class LightNode;
class CameraNode;

class SceneGraph;

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to convert the scengraph to a (opimized) sequence.
///
////////////////////////////////////////////////////////////////////////////////

class Optimizer {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs an Optimizer.
        ///
        ////////////////////////////////////////////////////////////////////////
        Optimizer();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys an Optimizer.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Optimizer();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Takes the Scengraph and processes geometry, light and camera lists.
        ///
        ///\param scene_graph          The SceneGraph to be processed.
        ////////////////////////////////////////////////////////////////////////
        void check( SceneGraph const* scene_graph );

        OptimizedScene const& get_data() const;

    private:
        OptimizedScene data_;

};

}

#endif // OPTIMIZER_HPP
