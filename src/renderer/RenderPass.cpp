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
/// \brief Definition of the RenderPass class.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "renderer/RenderPass.hpp"

// guacamole headers
#include "renderer/RenderPipeline.hpp"
#include "renderer/LightInformation.hpp"
#include "renderer/TextureBase.hpp"
#include "renderer/GeometryBase.hpp"
#include "renderer/MaterialBase.hpp"
#include "traverser/Optimizer.hpp"
#include "utils/debug.hpp"
#include "utils/Profiler.hpp"

namespace gua {

////////////////////////////////////////////////////////////////////////////////

RenderPass::
RenderPass(std::string const& name, std::string const& camera,
           std::string const& screen, std::string const& render_mask,
           float width, float height, bool size_is_relative):

    GenericRenderPass(name, camera, screen, render_mask,
                      width, height, size_is_relative),
    inputs_(),
    texture_uniforms_(),
    float_uniforms_(),
    light_information_(NULL) {}

////////////////////////////////////////////////////////////////////////////////

RenderPass::
~RenderPass() {

    if (light_information_) delete light_information_;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPass::
set_input_buffer(std::string const& in_render_pass,
                 std::string const& in_buffer,
                 std::string const& target_material,
                 std::string const& target_uniform) {

    inputs_[target_material][target_uniform] = std::make_pair(in_render_pass,
                                                              in_buffer);
}

////////////////////////////////////////////////////////////////////////////////

void RenderPass::
overwrite_uniform_float(std::string const& material,
                        std::string const& uniform_name, float value) {

    float_uniforms_[material][uniform_name] = value;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPass::
overwrite_uniform_texture(std::string const& material,
                          std::string const& uniform_name,
                          std::shared_ptr<Texture> const& value) {

    texture_uniforms_[material][uniform_name] = value;
}

////////////////////////////////////////////////////////////////////////////////

void RenderPass::
overwrite_uniform_texture(std::string const& material,
                          std::string const& uniform_name,
                          std::string const& texture_name) {

    texture_uniforms_[material][uniform_name] = TextureBase::instance()->
                                                              get(texture_name);
}

////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<Texture> RenderPass::
get_buffer(std::string const& name, CameraMode mode, bool draw_fps) {

    // check for existance of desired buffer
    if ((mode == CENTER
            && center_eye_buffers_.find(name) == center_eye_buffers_.end())
     || (mode == LEFT
            && left_eye_buffers_.find(name)  == left_eye_buffers_.end())
     || (mode == RIGHT
            && right_eye_buffers_.find(name) == right_eye_buffers_.end())) {

        WARNING("Failed to get buffer \"%s\" from pass \"%s\": "
                "A buffer with this name does not exist!",
                name.c_str(), get_name().c_str());
        return NULL;
    }

    // return appropriate buffer if it has been rendered already
    if (mode == CENTER && rendererd_center_eye_)
        return center_eye_buffers_[name];

    if (mode == LEFT && rendererd_left_eye_)
        return left_eye_buffers_[name];

    if (mode == RIGHT && rendererd_right_eye_)
        return right_eye_buffers_[name];

    // serialize the scenegraph
    Optimizer optimizer;
    optimizer.check(pipeline_->get_current_graph(), render_mask_);

    // if there are dynamic texture inputs for this render pass, get the
    // according buffers recursively
    for (auto& node: optimizer.get_data().nodes_) {
        auto material(inputs_.find(node.material_));

        if (material != inputs_.end()) {
            for (auto& uniform: material->second) {
                overwrite_uniform_texture(material->first, uniform.first,
                              pipeline_->get_render_pass(uniform.second.first)->
                              get_buffer(uniform.second.second, mode));
            }
        }
    }
    // we'll need these two very often now...
    OptimizedScene const& scene(optimizer.get_data());
    RenderContext const& ctx(pipeline_->get_context());

    // get the fbo which should be rendered to
    FrameBufferObject* fbo(NULL);

    switch (mode) {
        case CENTER:
            fbo = &center_eye_fbo_;
            break;
        case LEFT:
            fbo = &left_eye_fbo_;
            break;
        case RIGHT:
            fbo = &right_eye_fbo_;
            break;
    }

    fbo->bind(ctx);

    fbo->clear_color_buffers(ctx);
    fbo->clear_depth_stencil_buffer(ctx);

    ctx.render_context->set_viewport(scm::gl::viewport(math::vec2(0,0),
                                                    math::vec2(fbo->width(),
                                                               fbo->height())));

    auto camera_it(scene.cameras_.find(camera_));
    auto screen_it(scene.screens_.find(screen_));

    if (camera_it != scene.cameras_.end()
        && screen_it != scene.screens_.end()) {

        auto camera(camera_it->second);
        auto screen(screen_it->second);

        math::mat4 camera_transform(camera.transform_);
        if (mode == LEFT) {
            scm::math::translate(camera_transform,
                                 -camera.stereo_width_*0.5f, 0.f, 0.f);
        } else if (mode == RIGHT) {
            scm::math::translate(camera_transform,
                                 camera.stereo_width_*0.5f, 0.f, 0.f);
        }

        auto projection(math::compute_frustum(camera_transform.column(3),
                                              screen.transform_,
                                              0.1, 100000.f));

        math::mat4 view_transform(screen.transform_);
        view_transform[12] = 0.f;
        view_transform[13] = 0.f;
        view_transform[14] = 0.f;
        view_transform[15] = 1.f;

        math::vec3 camera_position(camera_transform.column(3)[0],
                                   camera_transform.column(3)[1],
                                   camera_transform.column(3)[2]);

        view_transform = scm::math::make_translation(camera_position)
                         * view_transform;

        math::mat4 view_matrix(scm::math::inverse(view_transform));

        // update light data uniform block
        if (scene.lights_.size() > 0) {

            if (!light_information_) {
                light_information_ =
                new scm::gl::uniform_block<LightInformation>(ctx.render_device);
            }

            light_information_->begin_manipulation(ctx.render_context);

            LightInformation light;

            light.light_count = math::vec4i(scene.lights_.size(),
                                            scene.lights_.size(),
                                            scene.lights_.size(),
                                            scene.lights_.size());

            for (unsigned i(0); i < scene.lights_.size(); ++i) {

                math::mat4 transform(scene.lights_[i].transform_);

                // calc light radius and position
                light.position[i] = math::vec4(transform[12], transform[13],
                                               transform[14], transform[15]);
                float radius = scm::math::length(light.position[i] - transform
                                              * math::vec4(0.f, 0.f, 1.f, 1.f));

                light.color_radius[i] = math::vec4(scene.lights_[i].color_.r(),
                                                   scene.lights_[i].color_.g(),
                                                   scene.lights_[i].color_.b(),
                                                   radius);
            }

            **light_information_ = light;

            light_information_->end_manipulation();

            ctx.render_context->bind_uniform_buffer(
                                         light_information_->block_buffer(), 0);
        }

        for (auto& core: scene.nodes_) {

            auto geometry = GeometryBase::instance()->get(core.geometry_);
            auto material = MaterialBase::instance()->get(core.material_);

            if (material && geometry) {
                material->use(ctx);

                if (float_uniforms_.find(core.material_)
                    != float_uniforms_.end())  {

                    for (auto val : float_uniforms_[core.material_])
                        material->get_shader()->set_float(ctx, val.first,
                                                          val.second);
                }

                if (texture_uniforms_.find(core.material_)
                    != texture_uniforms_.end()) {

                    for (auto val : texture_uniforms_[core.material_])
                        material->get_shader()->set_sampler2D(ctx, val.first,
                                                              *val.second);
                }

                material->get_shader()->set_mat4(ctx, "projection_matrix",
                                                 projection);

                material->get_shader()->set_mat4(ctx, "view_matrix",
                                                 view_matrix);

                material->get_shader()->set_mat4(ctx, "model_matrix",
                                                 core.transform_);

                material->get_shader()->set_mat4(ctx, "normal_matrix",
                                          scm::math::transpose(
                                          scm::math::inverse(core.transform_)));

                geometry->draw(ctx);

                material->unuse(ctx);

            } else if (material) {
                WARNING("Cannot render geometry \"%s\": Undefined geometry "
                        "name!", core.geometry_.c_str());

            } else if (geometry) {
                WARNING("Cannot render geometry \"%s\": Undefined material "
                        "name: \"%s\"!", core.geometry_.c_str(),
                        core.material_.c_str());

            } else {
                WARNING("Cannot render geometry \"%s\": Undefined geometry "
                        "and material name: \"%s\"!", core.geometry_.c_str(),
                        core.material_.c_str());
            }
        }

        if (scene.lights_.size() > 0) {
            ctx.render_context->reset_uniform_buffers();
        }
    }

    fbo->unbind(ctx);

    // draw fps on the screen
    if (draw_fps) {
        if (!text_renderer_)
            text_renderer_ = new TextRenderer(pipeline_->get_context());

        if (mode == CENTER) {
            text_renderer_->render_fps(pipeline_->get_context(), center_eye_fbo_,
                                       pipeline_->get_application_fps(),
                                       pipeline_->get_rendering_fps());
        } else if (mode == LEFT) {
            text_renderer_->render_fps(pipeline_->get_context(), left_eye_fbo_,
                                       pipeline_->get_application_fps(),
                                       pipeline_->get_rendering_fps());
        } else {
            text_renderer_->render_fps(pipeline_->get_context(), right_eye_fbo_,
                                       pipeline_->get_application_fps(),
                                       pipeline_->get_rendering_fps());
        }
    }

    // return the buffer and set the already-rendered-flag
    if (mode == CENTER) {
        rendererd_center_eye_ = true;
        return center_eye_buffers_[name];
    } else if (mode == LEFT) {
        rendererd_left_eye_ = true;
        return left_eye_buffers_[name];
    } else {
        rendererd_right_eye_ = true;
        return right_eye_buffers_[name];
    }
}

////////////////////////////////////////////////////////////////////////////////

}
