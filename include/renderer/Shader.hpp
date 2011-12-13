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
/// \brief Declaration of the Shader class.
////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include "include/utils/TextFile.hpp"

class RenderContext;

////////////////////////////////////////////////////////////////////////////////
/// \brief A base class for Fragment- and VertexShaders.
///
/// It is used to upload shader information to the GPU.
////////////////////////////////////////////////////////////////////////////////

class Shader {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        ////////////////////////////////////////////////////////////////////////
        Shader();

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param file_name
        /// \param shader_type
        ////////////////////////////////////////////////////////////////////////
        Shader(std::string const& file_name, unsigned shader_type);

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~Shader();

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param context
        /// \return
        ////////////////////////////////////////////////////////////////////////
        unsigned get_id(RenderContext const& context) const;

    private:
        void upload_to(RenderContext const& context) const;
        void validate_shader(unsigned shader) const;

        mutable std::vector<unsigned> shader_ids_;
        unsigned shader_type_;
        mutable TextFile source_;
};

#endif // SHADER_HPP
