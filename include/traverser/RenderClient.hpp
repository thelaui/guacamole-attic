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
/// \brief Declaration of the CameraCore class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDERCLIENT_HPP
#define GUA_RENDERCLIENT_HPP

#include <vector>
#include <string>
#include <thread>
#include <condition_variable>

#include "scenegraph/SceneGraph.hpp"
#include "utils/Timer.hpp"

namespace gua {

class RenderPipeline;

////////////////////////////////////////////////////////////////////////////////
/// \brief This class represents one render thread.
///
////////////////////////////////////////////////////////////////////////////////

class RenderClient {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a new RenderClient.
        ///
        ////////////////////////////////////////////////////////////////////////
        RenderClient(RenderPipeline* pipeline);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys a RenderClient.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~RenderClient();

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

