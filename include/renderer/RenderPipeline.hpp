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


#include <map>

#include "renderer/RenderWindow.hpp"

namespace gua {

class GenericRenderPass;
class SceneGraph;

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
///
////////////////////////////////////////////////////////////////////////////////
class RenderPipeline {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        RenderPipeline(RenderWindow::Description const& window);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        ~RenderPipeline();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void add_render_pass(GenericRenderPass* pass);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        GenericRenderPass* get_render_pass(std::string const& pass_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        SceneGraph const* get_current_graph() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        RenderContext const& get_context() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        void set_final_buffer(std::string const& pass_name,
                              std::string const& buffer_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        StereoMode get_stereo_mode() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
        ////////////////////////////////////////////////////////////////////////
        float get_application_fps() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Deletes the Material and frees all associated data.
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



