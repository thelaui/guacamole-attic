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
/// \brief Declaration of the Core class.
////////////////////////////////////////////////////////////////////////////////

#ifndef CORE_HPP
#define CORE_HPP

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to represent certain Node properties.
///
/// Cores determine the type of a Node. Accordingly they can be referred to as
/// lights, geometry or camera nodes.
///
////////////////////////////////////////////////////////////////////////////////

class Core {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// This enum is used to distinguish Cores with different properties
        /// from each other.
        ////////////////////////////////////////////////////////////////////////
        enum CoreType { CAMERA, GEOMETRY, LIGHT };

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a Core.
        ///
        ///\param type      The Core's type
        ////////////////////////////////////////////////////////////////////////
        Core(CoreType type);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destructs a Core.
        ////////////////////////////////////////////////////////////////////////
        virtual ~Core();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Returns the Core's type.
        ///
        /// This function can be used to find out on which derived Core class
        /// a Core pointer has to be casted.
        ///
        ///\return type      The Core's type
        ////////////////////////////////////////////////////////////////////////
        CoreType get_type() const;

    private:
        CoreType type_;

};

#endif // CORE_HPP
