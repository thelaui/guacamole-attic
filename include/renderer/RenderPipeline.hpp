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
/// \brief Declaration of the RenderPipeline class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDER_PIPELINE_HPP
#define GUA_RENDER_PIPELINE_HPP

// guacamole headers
#include "renderer/RenderWindow.hpp"
#include "utils/Profiler.hpp"

// external headers
#include <map>

namespace gua {

class GenericRenderPass;
class SceneGraph;

////////////////////////////////////////////////////////////////////////////////
/// \brief A rendering pipeline describes how an image is generated.
///
/// A rendering pipeline consists of multiple passes. These are rendering parts
/// of (or the entire) SceneGraph to buffers. These buffers may be used as input
/// for other passes. One final buffer of a final pass is shown on the screen.
////////////////////////////////////////////////////////////////////////////////
class RenderPipeline {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Creates a new RenderPipeline.
        ///
        /// \param window           The description of the window which should
        ///                         be opened by this pipe.
        ////////////////////////////////////////////////////////////////////////
        RenderPipeline(RenderWindow::Description const& window);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the RenderPipeline and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        ~RenderPipeline();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a render pass to the pipe.
        ///
        /// Adds a new render pass to the pipe. It should have an unique among
        /// the passes of this pipe, else it won't function properly.
        ///
        /// \param pass             The pass to be added.
        ////////////////////////////////////////////////////////////////////////
        void add_render_pass(GenericRenderPass* pass);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns a render pass.
        ///
        /// Retrieves a previously added pass from the pipe.
        ///
        /// \param pass_name        The name of the desired pass.
        /// \return                 The desired pass or NULL if it doesn't
        ///                         exist.
        ////////////////////////////////////////////////////////////////////////
        GenericRenderPass* get_render_pass(std::string const& pass_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the graph of this pipe.
        ///
        /// \return                 A pointer to the pipe's copy of the current
        ///                         scene. This pointer invalidates after each
        ///                         frame. Use with care.
        ////////////////////////////////////////////////////////////////////////
        SceneGraph const* get_current_graph() const;

        /////////////////////////////////////////////////////////////////////////
        /// \brief Get the RenderContext of this pipe.
        ///
        /// Can be called in order to retrieve the RenderContext of the
        /// RenderWindow created by this pipe.
        ///
        /// \return The context owned by this pipe's window.
        ////////////////////////////////////////////////////////////////////////
        RenderContext const& get_context() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Sets the buffer displayed on screen.
        ///
        /// Specifies which buffer from which pass should be displayed on the
        /// screen.
        ///
        /// \param pass_name        The name of the target pass.
        /// \param buffer_name      The name of the target buffer.
        ////////////////////////////////////////////////////////////////////////
        void set_final_buffer(std::string const& pass_name,
                              std::string const& buffer_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the stereo mode of this pipe.
        ///
        /// \return                 The stereo mode of this pipe.
        ////////////////////////////////////////////////////////////////////////
        StereoMode get_stereo_mode() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the FPS of the application loop.
        ///
        /// \return                 Returns the rate at which the queue_draw
        ///                         call fired. Should be aproximately the same
        ///                         among all pipes.
        ////////////////////////////////////////////////////////////////////////
        float get_application_fps() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets the FPS of the rendering loop.
        ///
        /// \return                 Returns the rate at which the pipe is
        ///                         actually rendering.
        ////////////////////////////////////////////////////////////////////////
        float get_rendering_fps() const;

        friend class RenderClient;

    private:
        void process(SceneGraph* graph, float application_fps,
                     float rendering_fps);

        void create_buffers();

        RenderWindow* window_;
        RenderWindow::Description window_description_;
        std::string final_pass_, final_buffer_;
        std::map<std::string, GenericRenderPass*> passes_;

        SceneGraph* current_graph_;

        float application_fps_, rendering_fps_;
};

}

#endif // GUA_RENDER_PIPELINE_HPP



