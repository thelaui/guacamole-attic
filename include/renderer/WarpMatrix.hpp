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
/// \brief Declaration of the WarpMatrix class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_WARP_MATRIX_HPP
#define GUA_WARP_MATRIX_HPP

// guacamole headers
#include "renderer/Texture.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief A class representing a warp matrix.
///
/// Warp matrices are used to align colors of pixels of an projected image,
/// when the projecting beamers for the colors red, green and blue don't
/// overlap exactly.
////////////////////////////////////////////////////////////////////////////////
class WarpMatrix : public Texture {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) WarpMatrix.
        ////////////////////////////////////////////////////////////////////////
        WarpMatrix();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new WarpMatrix from a given path to a warp matrix file.
        ///
        /// \param file_name            Path to a warp matrix file.
        ////////////////////////////////////////////////////////////////////////
        WarpMatrix(std::string const& file_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Clears all associated buffers.
        ////////////////////////////////////////////////////////////////////////
        ~WarpMatrix();

    private:
        /*virtual*/ void upload_to(RenderContext const& context) const;

        mutable std::vector<float> data_;

};

}
# endif // GUA_WARP_MATRIX_HPP



