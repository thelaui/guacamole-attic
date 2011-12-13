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
/// \brief Declaration of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <eigen2/Eigen/Core>

#include "include/renderer/FragmentShader.hpp"
#include "include/renderer/VertexShader.hpp"
#include "include/renderer/Uniform.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief An actual shader which can be applied to the Graphics pipeline.
///
/// It combines data from a FragmentShader and a VertexShader in order to
/// achieve different visual appearances of the same mesh.
////////////////////////////////////////////////////////////////////////////////

class ShaderProgram {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram();

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param v_shader
        /// \param f_shader
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader );

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~ShaderProgram();

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param context
        ////////////////////////////////////////////////////////////////////////
        void use(RenderContext const& context) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param context
        /// \param projection_matrix
        ////////////////////////////////////////////////////////////////////////
        void set_projection_matrix(RenderContext const& context, Eigen::Matrix4f const& projection_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param context
        /// \param view_matrix
        ////////////////////////////////////////////////////////////////////////
        void set_view_matrix(RenderContext const& context, Eigen::Matrix4f const& view_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ///
        ///
        /// \param context
        /// \param model_matrix
        ////////////////////////////////////////////////////////////////////////
        void set_model_matrix(RenderContext const& context, Eigen::Matrix4f const& model_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ////////////////////////////////////////////////////////////////////////
        const static unsigned vertex_location = 0;

        ////////////////////////////////////////////////////////////////////////
        /// \brief
        ////////////////////////////////////////////////////////////////////////
        const static unsigned normal_location = 1;

    private:
        void upload_to(RenderContext const& context) const;
        mutable std::vector<unsigned> program_ids_;

        mutable std::vector<Uniform> projection_matrix_;
        mutable std::vector<Uniform> view_matrix_;
        mutable std::vector<Uniform> model_matrix_;
        mutable std::vector<Uniform> normal_matrix_;

        VertexShader v_shader_;
        FragmentShader f_shader_;
};

#endif // SHADERPROGRAM_HPP
