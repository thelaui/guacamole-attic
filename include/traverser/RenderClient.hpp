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

#ifndef RENDERCLIENT_HPP
#define RENDERCLIENT_HPP

#include <vector>
#include <string>
#include <thread>
#include <condition_variable>

#include "renderer/RenderWindow.hpp"
#include "include/traverser/OptimizedScene.hpp"

namespace gua {

class RenderBackend;
class CameraNode;
class GeometryNode;
class LightNode;

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
        RenderClient(int width, int height, std::string const& camera, std::string const& display);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Destructor.
        ///
        /// This destroys a RenderClient.
        ///
        ////////////////////////////////////////////////////////////////////////
        virtual ~RenderClient();

        void queue_draw(OptimizedScene const& scene);

        std::string const& get_camera_name() const;

    private:
        void draw_loop();

        std::thread* draw_thread_;
        RenderBackend* render_backend_;

        bool rendering_finished_;
        std::mutex render_mutex_;
        std::condition_variable render_condition_;

        int width_;
        int height_;
        std::string camera_;
        std::string display_;

        unsigned frame_;

        OptimizedScene current_scene_;
};

}

#endif // RENDERCLIENT_HPP

