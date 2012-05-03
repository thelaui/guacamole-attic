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

#ifndef GUA_OPTIMIZER_HPP
#define GUA_OPTIMIZER_HPP

#include "traverser/OptimizedScene.hpp"
#include "traverser/RenderMask.hpp"

namespace gua {

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
        void check( SceneGraph const* scene_graph, RenderMask const& render_mask );

        OptimizedScene const& get_data() const;

    private:
        OptimizedScene data_;

};

}

#endif // GUA_OPTIMIZER_HPP
