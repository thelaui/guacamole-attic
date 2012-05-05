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
/// \brief Declaration of the CameraCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDERCLIENT_HPP
#define GUA_RENDERCLIENT_HPP

// guacamole headers
#include "scenegraph/SceneGraph.hpp"
#include "utils/Timer.hpp"

// external headers
#include <vector>
#include <string>
#include <thread>
#include <condition_variable>

namespace gua {

class RenderPipeline;

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents one render thread.
///
/// The queue_draw method is directly called by the RenderServer. Internally it
/// uses a threaded rendering loop which always waits for queue_draw calls. When
/// it fails to finish rendering before the next queue_draw is called, it will
/// ignore this call.
////////////////////////////////////////////////////////////////////////////////
class RenderClient {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a new RenderClient.
        ///
        /// \param pipeline         The pipeline which should be processed by
        ///                         this RenderClient.
        ////////////////////////////////////////////////////////////////////////
        RenderClient(RenderPipeline* pipeline);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// This destroys a RenderClient.
        ////////////////////////////////////////////////////////////////////////
        virtual ~RenderClient();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Draw the scene.
        ///
        /// This requests a drawing operation of the given graph. If the client
        /// is still processing the last call of this function it will be
        /// ignored.
        ///
        /// \param graph            A pointer to the graph which
        ///                         should be drawn.
        ////////////////////////////////////////////////////////////////////////
        void queue_draw(SceneGraph const* graph);

    private:
        void draw_loop();

        std::thread* draw_thread_;
        RenderPipeline* render_pipeline_;
        SceneGraph graph_copy_;

        float application_fps_, rendering_fps_;
        unsigned application_frame_count_, rendering_frame_count_;
        Timer application_timer_, rendering_timer_;

        bool rendering_finished_;
        std::mutex render_mutex_;
        std::condition_variable render_condition_;
};

}

#endif // GUA_RENDERCLIENT_HPP

