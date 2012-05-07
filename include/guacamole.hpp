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
/// \brief The main include file of guacamole.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_GUACAMOLE_HPP
#define GUA_GUACAMOLE_HPP

#include "renderer/GeometryBase.hpp"
#include "renderer/MaterialBase.hpp"
#include "renderer/TextureBase.hpp"
#include "renderer/RenderPipeline.hpp"
#include "renderer/RenderPass.hpp"
#include "renderer/FullscreenPass.hpp"
#include "renderer/enums.hpp"
#include "traverser/RenderServer.hpp"
#include "scenegraph/Iterator.hpp"
#include "scenegraph/SceneGraph.hpp"
#include "cores/GeometryCore.hpp"
#include "cores/CameraCore.hpp"
#include "cores/LightCore.hpp"
#include "cores/ScreenCore.hpp"
#include "utils/PathParser.hpp"
#include "utils/DotGenerator.hpp"
#include "utils/Directory.hpp"
#include "utils/Timer.hpp"
#include "utils/debug.hpp"
#include "utils/math.hpp"
#include "utils/randomizer.hpp"
#include "utils/string_utils.hpp"
#include "utils/Profiler.hpp"

namespace gua {

    ////////////////////////////////////////////////////////////////////////
    /// \brief Initialize guacamole.
    ///
    /// This should be called once in every application using guacamole.
    ////////////////////////////////////////////////////////////////////////

    void init(int argc, char** argv);
}

#endif // GUA_GUACAMOLE_HPP

////////////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \section welcome Welcome to guacamole!
/// Welcome to guacamole, an incredibly exciting wanna-be-scene-graph. Someday it
/// will include the latest OpenGL features, cutting edge multipe support and
/// much, much more! Until then... stay tuned!
/// \section example A short example
/// Below you can discover a little example of guacamole displaying some
/// rotating monkeys.
/// \code
/// #include "guacamole.hpp"
///
/// #include <thread>
///
/// void render(gua::SceneGraph* graph, std::string const& display) {
///     gua::Renderer renderer;
///     try {
///         renderer.add_display(800, 600, display);
///         renderer.start_render_loop(graph);
///     } catch (std::string& error) {
///         std::cerr<<error<<std::endl;
///     }
/// }
///
/// int main() {
///     gua::RenderWindow::init();
///
///     gua::GeometryBase::load_presets();
///     gua::MaterialBase::load_presets();
///
///     gua::SceneGraph graph;
///
///     auto camera_core = new gua::CameraCore(60.f, 4.f/3.f, 0.1f, 1000.f);
///     auto camera = graph.add_node("/", "camera", camera_core);
///     camera.translate(0.5, 1, 2);
///     camera.rotate(0.2, 0, 1, 0);
///
///     auto cube_core = new gua::GeometryCore("cube", "matt");
///     auto floor = graph.add_node("/", "floor", cube_core);
///     floor.scale(4, 0.1, 4);
///
///     auto box = graph.add_node("/", "box", cube_core);
///     box.scale(0.5, 0.5, 0.5);
///     box.translate(-1, 1, 0);
///
///     auto monkey_core = new gua::GeometryCore("monkey", "shiny");
///     auto monkey = graph.add_node("/box", "monkey", monkey_core);
///     monkey.translate(0, 2, 0);
///
///     monkey = graph.add_node("/box/monkey", "monkey", monkey_core);
///     monkey.scale(0.3, 0.3, 0.3);
///     monkey.translate(0, 5, 0);
///
///     std::thread render_thread(render, &graph, ":0.0");
///
///     while (true) {
///         std::this_thread::sleep_for(std::chrono::milliseconds(1));
///         graph["/box"].rotate(0.001, 0, 1, 0);
///         graph["/box/monkey"].rotate(0.001, 1, 0, 0);
///         graph["/box/monkey/monkey"].rotate(0.01, 0, 1, 0);
///     }
///
///     return 0;
/// }
/// \endcode
////////////////////////////////////////////////////////////////////////////////
