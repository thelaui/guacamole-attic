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
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_SHADERPROGRAM_HPP
#define GUA_SHADERPROGRAM_HPP

#include <map>

#include "renderer/Texture.hpp"
#include "renderer/Uniform.hpp"
#include "utils/Color3f.hpp"
#include "utils/math.hpp"

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
        void create_from_files(std::string const& v_shader_file, std::string const& f_shader_file);

        void create_from_sources(std::string const& v_shader_source, std::string const& f_shader_source);

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

        void unuse(RenderContext const& context) const;

        void set_mat4(RenderContext const& context, std::string const& mat_name,
                      math::mat4 const& mat);

        void set_vec2(RenderContext const& context, std::string const& vec_name,
                      math::vec2 const& vec);

        void set_vec3(RenderContext const& context, std::string const& vec_name,
                      math::vec3 const& vec);

        void set_color3f(RenderContext const& context, std::string const& color_name,
                      Color3f const& color);

        void set_vec4(RenderContext const& context, std::string const& vec_name,
                      math::vec4 const& vec);

        void set_sampler2D(RenderContext const& context, std::string const& sampler_name,
                           Texture const& sampler);

        void set_float(RenderContext const& context, std::string const& float_name,
                       float value);

        void set_int(RenderContext const& context, std::string const& int_name,
                     int value);

    private:

        void upload_to(RenderContext const& context) const;

        mutable std::vector<scm::gl::program_ptr> programs_;
        mutable std::vector<int> texture_offsets_;
        mutable std::mutex upload_mutex_;

        bool shaders_are_files_;

        std::string f_shader_;
        std::string v_shader_;
};

}

#endif // GUA_SHADERPROGRAM_HPP
