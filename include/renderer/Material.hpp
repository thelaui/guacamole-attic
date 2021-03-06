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
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
//
/// \file
/// \brief Declaration of the Material class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_MATERIAL_HPP
#define GUA_MATERIAL_HPP

// guacamole headers
#include "renderer/ShaderProgram.hpp"
#include "renderer/Texture.hpp"

// external headers
#include <memory>

namespace gua {

class RenderContext;
class TextFile;

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a Material.
///
/// Materials are defined by a fragment and a vertex shader. Additionally
/// uniforms of this shaders may be set to specific values.
////////////////////////////////////////////////////////////////////////////////
class Material {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Default constructor.
        ///
        /// Creates a new (invalid) material. It won't do anything until being
        /// initialized with the non-default constructor.
        ////////////////////////////////////////////////////////////////////////
        Material();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor from a material description.
        ///
        /// Creates a new Material from a given material description.
        ///
        /// \param file_name        The file used to describe this material.
        ////////////////////////////////////////////////////////////////////////
        Material(std::string const& file_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        ~Material();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Applies the Material.
        ///
        /// Any preceeding draw call will use this Material.
        ///
        /// \param context          The context which should use this Material.
        ////////////////////////////////////////////////////////////////////////
        void use(RenderContext const& context) const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Unuses the material.
        ///
        /// Preceeding draw calls won't use this material anymore.
        ///
        /// \param context          The context which should use this Material.
        ////////////////////////////////////////////////////////////////////////
        void unuse(RenderContext const& context) const;

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Overwrites a uniform value.
        ///
        /// With this method material uniforms may be overwritten.
        /// The uniforms will be set to the given values when the material
        /// is used.
        ///
        /// \param uniform_name     The name of the uniform to be overwritten.
        /// \param value            The value to which the uniform shall be set.
        ////////////////////////////////////////////////////////////////////////
        void set_uniform_float(std::string const& uniform_name, float value);

        void set_uniform_int(std::string const& uniform_name, int value);

        void set_uniform_texture(std::string const& uniform_name,
                                 std::shared_ptr<Texture> const& value);

        void set_uniform_texture(std::string const& uniform_name,
                                 std::string const& value);
        ///@}

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets specific GL states for this material.
        ///
        /// Deletes the Material and frees all associated data.
        ///
        /// \param state_desc       The state to be set when this material is
        ///                         used.
        ////////////////////////////////////////////////////////////////////////
        void set_blend_state(
                        scm::gl::blend_state_desc const& state_desc);

        void set_rasterizer_state(
                        scm::gl::rasterizer_state_desc const& state_desc);

        void set_depth_stencil_state(
                        scm::gl::depth_stencil_state_desc const& state_desc);
        ///@}

        ////////////////////////////////////////////////////////////////////////
        /// \brief Get the internal shader.
        ///
        /// Returns the internally used ShaderProgram.
        ///
        /// \return The shader of this Material.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram* get_shader() const;

    private:
        void construct_from_file(TextFile const& file);

        std::map<std::string, std::shared_ptr<Texture>> texture_uniforms_;
        std::map<std::string, float> float_uniforms_;
        std::map<std::string, int> int_uniforms_;
        ShaderProgram* shader_;

        scm::gl::blend_state_desc blend_state_desc_;
        scm::gl::rasterizer_state_desc rasterizer_state_desc_;
        scm::gl::depth_stencil_state_desc depth_stencil_state_desc_;

        mutable scm::gl::blend_state_ptr blend_state_;
        mutable scm::gl::rasterizer_state_ptr rasterizer_state_;
        mutable scm::gl::depth_stencil_state_ptr depth_stencil_state_;
};

}

#endif // GUA_MATERIAL_HPP


