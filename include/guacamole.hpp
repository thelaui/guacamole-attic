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
/// \brief The main include file of guacamole.
////////////////////////////////////////////////////////////////////////////////

#include "include/renderer/GeometryBase.hpp"
#include "include/renderer/MaterialBase.hpp"
#include "include/traverser/Renderer.hpp"
#include "include/scenegraph/Iterator.hpp"
#include "include/scenegraph/SceneGraph.hpp"
#include "include/scenegraph/GeometryCore.hpp"
#include "include/scenegraph/CameraCore.hpp"
#include "include/scenegraph/LightCore.hpp"

////////////////////////////////////////////////////////////////////////////////
/// \mainpage
/// \section welcome Welcome to guacamole!
/// Welcome to guacamole, a incredibly exciting wanna-be-scene-graph. Someday it
/// will include the latest OpenGL features, cutting edge multipe support and
/// much, much more! Until then... stay tuned!
/// \section example A short example
/// Below you can discover a little example of guacamole displaying some
/// rotating monkeys.
/// \code
/// #include "include/guacamole.hpp"
///
/// #include <thread>
///
/// void render(SceneGraph* graph, std::string const& display) {
///     Renderer renderer(800, 600, display);
///     renderer.start_render_loop(*graph);
/// }
///
/// int main() {
///     RenderWindow::init();
///
///     GeometryBase::load_presets();
///     MaterialBase::load_presets();
///
///     SceneGraph graph;
///
///     auto camera_core = new CameraCore(60.f, 4.f/3.f, 0.1f, 1000.f);
///     auto camera = graph.add_node("/", "camera", camera_core);
///     camera.translate(0.5, 1, 2);
///     camera.rotate(0.2, 0, 1, 0);
///
///     auto cube_core = new GeometryCore("cube", "matt");
///     auto floor = graph.add_node("/", "floor", cube_core);
///     floor.scale(4, 0.1, 4);
///
///     auto box = graph.add_node("/", "box", cube_core);
///     box.scale(0.5, 0.5, 0.5);
///     box.translate(-1, 1, 0);
///
///     auto monkey_core = new GeometryCore("monkey", "shiny");
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
