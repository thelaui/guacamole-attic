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
/// \brief Declaration of the RenderPass class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_FULLSCREEN_PASS_HPP
#define GUA_FULLSCREEN_PASS_HPP

#include <scm/gl_util/primitives/quad.h>
#include <scm/gl_core/buffer_objects/uniform_buffer_adaptor.h>

#include "renderer/GenericRenderPass.hpp"

namespace gua {

class LightInformation;

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
class FullscreenPass : public GenericRenderPass{
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        FullscreenPass(std::string const& name, std::string const& camera,
                       std::string const& screen, std::string const& material,
                       std::string const& render_mask = "", float width = 1.f,
                       float height = 1.f, bool size_is_relative = true);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        virtual ~FullscreenPass();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void set_input_buffer(std::string const& in_render_pass,
                               std::string const& in_buffer,
                               std::string const& target_uniform);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void overwrite_uniform_float(std::string const& uniform_name,
                                     float value);
        void overwrite_uniform_texture(std::string const& uniform_name,
                                        std::shared_ptr<Texture> const& value);
        void overwrite_uniform_texture(std::string const& uniform_name,
                                        std::string const& texture_name);

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


