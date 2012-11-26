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
/// \brief Declaration of the ShaderProgram class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_SHADERPROGRAM_HPP
#define GUA_SHADERPROGRAM_HPP

// guacamole headers
#include "renderer/Texture.hpp"
#include "utils/Color3f.hpp"
#include "utils/math.hpp"

// external headers
#include <mutex>
#include <map>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief An actual shader which can be applied to the Graphics pipeline.
///
/// It combines data from a FragmentShader and a VertexShader in order to
/// achieve different visual appearances of the same mesh.
////////////////////////////////////////////////////////////////////////////////
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
        /// This method takes a vertex shader file and a fragment shader file
        /// and combines them to a ShaderProgram.
        ///
        /// \param v_shader_file        The VertexShader file path.
        /// \param f_shader_file        The FragmentShader file path.
        ////////////////////////////////////////////////////////////////////////
        void create_from_files(std::string const& v_shader_file,
                               std::string const& f_shader_file);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This method takes a vertex shader source and a fragment shader
        /// source and combines them to a ShaderProgram.
        ///
        /// \param v_shader_source      The vertex shader source.
        /// \param f_shader_source      The fragment shader source.
        ////////////////////////////////////////////////////////////////////////
        void create_from_sources(std::string const& v_shader_source,
                                 std::string const& f_shader_source);

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
        /// \param context             The context which should use this shader.
        ////////////////////////////////////////////////////////////////////////
        void use(RenderContext const& context) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Unuses the shader.
        ///
        /// Preceeding draw calls won't use this shader anymore.
        ////////////////////////////////////////////////////////////////////////
        void unuse(RenderContext const& context) const;

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets an uniform value.
        ///
        /// Sets an uniform value of a currently used shader.
        ///
        /// \param context             The context which should use this shader.
        /// \param uniform             The name of the uniform to be set.
        /// \param value               The value to which the uniform should be
        ///                            set.
        ////////////////////////////////////////////////////////////////////////
        void set_mat4(RenderContext const& context,
                      std::string const& uniform,
                      math::mat4 const& value);

        void set_vec2(RenderContext const& context,
                      std::string const& uniform,
                      math::vec2 const& value);

        void set_vec3(RenderContext const& context,
                      std::string const& uniform,
                      math::vec3 const& value);

        void set_color3f(RenderContext const& context,
                      std::string const& uniform,
                      Color3f const& color);

        void set_vec4(RenderContext const& context,
                      std::string const& uniform,
                      math::vec4 const& value);

        void set_sampler2D(RenderContext const& context,
                      std::string const& uniform,
                      Texture const& value);

        void set_float(RenderContext const& context,
                      std::string const& uniform,
                      float value);

        void set_int(RenderContext const& context,
                      std::string const& uniform,
                      int value);
        ///@}

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
