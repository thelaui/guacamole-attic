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
/// \brief A database for accessing material data.
////////////////////////////////////////////////////////////////////////////////

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <eigen2/Eigen/Core>

#include "include/renderer/FragmentShader.hpp"
#include "include/renderer/VertexShader.hpp"
#include "include/renderer/Uniform.hpp"

class ShaderProgram {
    public:
        ShaderProgram();
        ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader );
        virtual ~ShaderProgram();

        void use(RenderContext const& context) const;

        void set_projection_matrix(RenderContext const& context, Eigen::Matrix4f const& projection_matrix) const;
        void set_view_matrix(RenderContext const& context, Eigen::Matrix4f const& view_matrix) const;
        void set_model_matrix(RenderContext const& context, Eigen::Matrix4f const& model_matrix) const;

        const static unsigned vertex_location = 0;
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