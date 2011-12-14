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
		///\brief check
        ///
        /// Takes the Scengraph and geometry, light and camera data.
        ///
        ///\param scene_graph          The SceneGraph to be processed.
        ////////////////////////////////////////////////////////////////////////
		void check( SceneGraph const* scene_graph );
	
		////////////////////////////////////////////////////////////////////////
		///\brief get the list of geometry
        ///
        ///
        ///\return geometry_data     a vector containing the scenes geometry data
        ////////////////////////////////////////////////////////////////////////
		std::vector<GeometryNode*> const& get_geometry_data() const;

		////////////////////////////////////////////////////////////////////////
		///\brief get the list of ligths
        ///
        ///
        ///\return light_data     a vector containing the lights within the scene
        ////////////////////////////////////////////////////////////////////////
		std::vector<LightNode*> const& get_light_data() const;

		////////////////////////////////////////////////////////////////////////
		///\brief get the list of cameras
        ///
        ///
        ///\return camera_data     a vector containing the camera in the scene
        ////////////////////////////////////////////////////////////////////////
		std::vector<CameraNode*> const& get_camera_data() const;	

	private:

		std::vector<GeometryNode*> geometry_data_;
		std::vector<LightNode*> light_data_;
		std::vector<CameraNode*> camera_data_;

};

#endif // OPTIMIZER_HPP
