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
/// \brief Declaration of the RenderPipeline class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_PIPELINE_HPP
#define RENDER_PIPELINE_HPP


namespace gua {

class RenderPipeline {
    public:
        RenderPipeline(RenderWindow const& window, CameraCore::Type stereo_mode = CameraCore::MONO);

        void add_render_pass(RenderPass* pass);
        RenderPass* get_render_pass(std::string const& pass_name) const;

        void set_final_pass(std::string const& pass_name, std::string const& buffer_name);

        friend class Renderer;

    private:
        void process();

        std::map<std::string, RenderPass*> passes_;

};

}

#endif // RENDER_PIPELINE_HPP



