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
#include <map>

#include "renderer/FragmentShader.hpp"
#include "renderer/VertexShader.hpp"
#include "renderer/Texture.hpp"
#include "renderer/Uniform.hpp"
#include "utils/Color3f.hpp"

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
        /// \brief Unapplies this shader.
        ///
        ////////////////////////////////////////////////////////////////////////
        void unuse() const;

        void set_mat4(RenderContext const& context, std::string const& mat_name,
                      Eigen::Matrix4f const& mat) const;

        void set_vec2(RenderContext const& context, std::string const& vec_name,
                      Eigen::Vector2f const& vec) const;

        void set_vec3(RenderContext const& context, std::string const& vec_name,
                      Eigen::Vector3f const& vec) const;

        void set_vec3(RenderContext const& context, std::string const& vec_name,
                      Color3f const& vec) const;

        void set_vec4(RenderContext const& context, std::string const& vec_name,
                      Eigen::Vector4f const& vec) const;

        void set_sampler2D(RenderContext const& context, std::string const& sampler_name,
                           Texture const& sampler) const;

        void set_float(RenderContext const& context, std::string const& float_name,
                       float value) const;

        void set_int(RenderContext const& context, std::string const& int_name,
                     int value) const;

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
        unsigned check_uniform(RenderContext const& context, std::string const& name,
                               Uniform::Type type) const;

        void upload_to(RenderContext const& context) const;
        mutable std::vector<unsigned> program_ids_;

        mutable std::vector<std::map<std::string, Uniform>> uniforms_;
        mutable int texture_offset_;

        VertexShader v_shader_;
        FragmentShader f_shader_;
};

}

#endif // SHADERPROGRAM_HPP
