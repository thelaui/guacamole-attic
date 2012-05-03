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
/// \brief Declaration of the RenderPass class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDER_PASS_HPP
#define GUA_RENDER_PASS_HPP

#include <scm/gl_core/buffer_objects/uniform_buffer_adaptor.h>

#include "renderer/GenericRenderPass.hpp"

namespace gua {

class LightInformation;

class RenderPass : public GenericRenderPass{
    public:
        RenderPass(std::string const& name, std::string const& camera, std::string const& screen, std::string const& render_mask = "",
                   float width = 1.f, float height = 1.f, bool size_is_relative = true);

        virtual ~RenderPass();

        void set_input_buffer(std::string const& in_render_pass, std::string const& in_buffer,
                              std::string const& target_material, std::string const& target_uniform);

        void overwrite_uniform_float(std::string const& material, std::string const& uniform_name, float value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::shared_ptr<Texture> const& value);
        void overwrite_uniform_texture(std::string const& material, std::string const& uniform_name, std::string const& texture_name);

        friend class RenderBackend;
        friend class RenderPipeline;

    private:
        /*virtual*/ std::shared_ptr<Texture> get_buffer(std::string const& name, CameraMode mode, bool draw_fps = false);

        // target material    target uniform        input pass             input buffer
        std::map<std::string, std::map<std::string, std::pair<std::string, std::string>>> inputs_;

        // target material    target uniform        input buffer
        std::map<std::string, std::map<std::string, std::shared_ptr<Texture>>> texture_uniforms_;

        // target material    target uniform        input value
        std::map<std::string, std::map<std::string, float>> float_uniforms_;

        scm::gl::uniform_block<LightInformation>* light_information_;
};

}

#endif // GUA_RENDER_PASS_HPP


