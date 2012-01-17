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

#include "renderer/FragmentShader.hpp"
#include "renderer/VertexShader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Uniform.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \brief An actual shader which can be applied to the Graphics pipeline.
///
/// It combines data from a FragmentShader and a VertexShader in order to
/// achieve different visual appearances of the same mesh.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class ShaderProgram {
    public:
        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) shader program.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from shaders.
        ///
        /// This method takes a VertexShader and a FragmentShader and combines
        /// them to a ShaderProgram.
        ///
        /// \param v_shader The VertexShader.
        /// \param f_shader The FragmentShader.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram( VertexShader const& v_shader, FragmentShader const& f_shader );

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Cleans all associated memory.
        ////////////////////////////////////////////////////////////////////////
        virtual ~ShaderProgram();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies this shader.
        ///
        /// All preceeding draw calls on the given context will be affected by
        /// this shader.
        ///
        /// \param context The context which should use this shader.
        ////////////////////////////////////////////////////////////////////////
        void use(RenderContext const& context) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the projection matrix.
        ///
        /// Sets the projection uniform for this shader.
        ///
        /// \param context           The context to be affected.
        /// \param projection_matrix The matrix which should be used for the
        ///                          projection matrix.
        ////////////////////////////////////////////////////////////////////////
        void set_projection_matrix(RenderContext const& context, Eigen::Matrix4f const& projection_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the view matrix.
        ///
        ///
        /// \param context     The context to be affected.
        /// \param view_matrix The matrix which should be used for the
        ///                    view matrix.
        ////////////////////////////////////////////////////////////////////////
        void set_view_matrix(RenderContext const& context, Eigen::Matrix4f const& view_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the model matrix.
        ///
        ///
        /// \param context      The context to be affected.
        /// \param model_matrix The matrix which should be used for the
        ///                     model matrix.
        ////////////////////////////////////////////////////////////////////////
        void set_model_matrix(RenderContext const& context, Eigen::Matrix4f const& model_matrix) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the diffuse texture.
        ///
        ///
        /// \param context      The context to be affected.
        /// \param texture      The matrix which should be used for the
        ///                     diffuse texture.
        ////////////////////////////////////////////////////////////////////////
        void set_diffuse(RenderContext const& context, Texture const& texture) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief The layout location of the vertex attribute.
        ////////////////////////////////////////////////////////////////////////
        const static unsigned vertex_location = 0;

        ////////////////////////////////////////////////////////////////////////
        /// \brief The layout location of the normal attribute.
        ////////////////////////////////////////////////////////////////////////
        const static unsigned normal_location = 1;

        ////////////////////////////////////////////////////////////////////////
        /// \brief The layout location of the texture attribute.
        ////////////////////////////////////////////////////////////////////////
        const static unsigned texture_location = 2;

    private:
        void upload_to(RenderContext const& context) const;
        mutable std::vector<unsigned> program_ids_;

        mutable std::vector<Uniform> projection_matrix_;
        mutable std::vector<Uniform> view_matrix_;
        mutable std::vector<Uniform> model_matrix_;
        mutable std::vector<Uniform> normal_matrix_;
        mutable std::vector<Uniform> diffuse_;

        VertexShader v_shader_;
        FragmentShader f_shader_;
};

}

#endif // SHADERPROGRAM_HPP
