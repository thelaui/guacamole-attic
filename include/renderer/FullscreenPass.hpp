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
/// \brief Declaration of the FullscreenPass class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_FULLSCREEN_PASS_HPP
#define GUA_FULLSCREEN_PASS_HPP

// guacamole headers
#include "renderer/GenericRenderPass.hpp"

// external headers
#include <scm/gl_util/primitives/quad.h>
#include <scm/gl_core/buffer_objects/uniform_buffer_adaptor.h>

namespace gua {

class LightInformation;

////////////////////////////////////////////////////////////////////////////////
/// \brief A RenderPass which automatically renders to a fullscreen quad.
///
/// This is especially useful for deferred shading or other post
/// processing purposes.
///
/// Render passes are part of a rendering pipeline. Basically they encapsulate
/// some FBOs to which the scene is rendered. The user has to add some color
/// buffers to this pass and a depth stencil buffer if desired. The scene is
/// rendered frome the point of view of a given camera through a given screen.
/// With render masks a part of the scene may be hidden.
////////////////////////////////////////////////////////////////////////////////
class FullscreenPass : public GenericRenderPass{
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new FullscreenPass.
        ///
        /// \param name             The name of this rendering pass.
        /// \param camera           The name of the camera used for this pass.
        /// \param screen           The name of the screen used for pass.
        /// \param material         The name of the material which should be
        ///                         used when drawing the fullscreen quad.
        /// \param render_mask      The rendering mask which should be applied
        ///                         to the scene before rendering this pass.
        ///                         This is only useful regarding lights, as
        ///                         there is no geometrie drawn.
        /// \param width            The width of this pass. Either relative to
        ///                         the window size or absolute pixel size.
        /// \param height           The height of this pass. Either relative to
        ///                         the window size or absolute pixel size.
        /// \param size_is_relative Determines whether width and height are
        ///                         interpreted as abolute or as releative.
        ////////////////////////////////////////////////////////////////////////
        FullscreenPass(std::string const& name, std::string const& camera,
                       std::string const& screen, std::string const& material,
                       std::string const& render_mask = "", float width = 1.f,
                       float height = 1.f, bool size_is_relative = true);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the FullscreenPass and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        virtual ~FullscreenPass();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets a texture input.
        ///
        /// Specifies a buffer from another Rendering pass, which should be
        /// used as input for a target uniform in the material shader of this
        /// FullscreenPass.
        ///
        /// \param in_render_pass   The name of the rendering pass which
        ///                         contains the desired buffer.
        /// \param in_buffer        The name of the desired buffer.
        /// \param target_uniform   The texture uniform which should be set to
        ///                         buffer.
        ////////////////////////////////////////////////////////////////////////
        void set_input_buffer(std::string const& in_render_pass,
                              std::string const& in_buffer,
                              std::string const& target_uniform);

        ///@{
        ////////////////////////////////////////////////////////////////////////
        /// \brief Overwrites a uniform value.
        ///
        /// With this method material uniforms may be overwritten for this pass.
        /// The uniforms will be set to the given values when the fullscreen
        /// quad is drawn.
        ///
        /// \param uniform_name     The name of the uniform to be overwritten.
        /// \param value            The value to which the uniform shall be set.
        ////////////////////////////////////////////////////////////////////////
        void overwrite_uniform_float(std::string const& uniform_name,
                                     float value);

        void overwrite_uniform_texture(std::string const& uniform_name,
                                       std::shared_ptr<Texture> const& value);

        void overwrite_uniform_texture(std::string const& uniform_name,
                                       std::string const& value);
        ///@}

    private:
        /*virtual*/ std::shared_ptr<Texture> get_buffer(std::string const& name,
                                                        CameraMode mode,
                                                        bool draw_fps = false);

        // target uniform        input pass             input buffer
        std::map<std::string, std::pair<std::string, std::string>> inputs_;

        // target uniform    input buffer
        std::map<std::string, std::shared_ptr<Texture>> texture_uniforms_;

        // target uniform    input value
        std::map<std::string, float> float_uniforms_;

        scm::gl::quad_geometry_ptr fullscreen_quad_;
        scm::gl::depth_stencil_state_ptr depth_stencil_state_;

        std::string material_name_;

        scm::gl::uniform_block<LightInformation>* light_information_;
};

}

#endif // GUA_FULLSCREEN_PASS_HPP


