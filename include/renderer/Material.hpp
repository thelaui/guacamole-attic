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
/// \brief Declaration of the Material class.
////////////////////////////////////////////////////////////////////////////////

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "renderer/ShaderProgram.hpp"
#include "renderer/Texture.hpp"

#include <memory>

namespace gua {

class RenderContext;
class TextFile;

////////////////////////////////////////////////////////////////////////////////
/// \brief Stores information on a Material.
///
/// For now, materials are defined by a shader only.
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
        /// \param file_name The file used to describe this material.
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
        /// \param context The context which should use this Material.
        ////////////////////////////////////////////////////////////////////////
        void use(RenderContext const& context) const;
        void unuse(RenderContext const& context) const;

        void set_uniform_float(std::string const& uniform_name, float value);
        void set_uniform_int(std::string const& uniform_name, int value);
        void set_uniform_texture(std::string const& uniform_name, std::shared_ptr<Texture> const& value);
        void set_uniform_texture(std::string const& uniform_name, std::string const& texture_name);

        void set_blend_state(bool enabled, unsigned src = GL_ONE, unsigned dest = GL_ONE);
        void set_rasterizer_state(bool cull_face, unsigned culling_mode);
        void set_depth_stencil_state(bool depth_test, bool write_depth);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Get the internal shader.
        ///
        /// Returns the internally used ShaderProgram.
        ///
        /// \return The shader of this Material.
        ////////////////////////////////////////////////////////////////////////
        ShaderProgram const& get_shader() const;

    private:
        void construct_from_file(TextFile const& file);

        std::map<std::string, std::shared_ptr<Texture>> texture_uniforms_;
        std::map<std::string, float> float_uniforms_;
        std::map<std::string, int> int_uniforms_;
        ShaderProgram* shader_;

        bool blend_enabled_;
        unsigned blend_src_, blend_dest_;
        bool cull_face_;
        unsigned culling_mode_;
        bool depth_test_, write_depth_;
};

}

#endif // MATERIAL_HPP


