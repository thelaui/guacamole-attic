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
/// \brief A utility class to generate DOT-files from a SceneGraph.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "utils/DotGenerator.hpp"

// guacamole headers
#include "scenegraph/SceneGraph.hpp"
#include "scenegraph/Iterator.hpp"
#include "cores/GeometryCore.hpp"

// external headers
#include <fstream>
#include <sstream>
#include <map>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

DotGenerator::
DotGenerator():
    parse_data_(),
    graph_name_() {}

////////////////////////////////////////////////////////////////////////////////

void DotGenerator::
parse_graph(SceneGraph const* graph, std::string const& name) {

    graph_name_ = name;
    parse_data_ += "graph " + graph_name_ + " { \n";

    std::map<int, int> added_nodes;

    int node_count(0);
    for (auto node(graph->begin()); node != graph->end(); ++node) {
        int current_depth(node.get_depth());
        std::stringstream node_name;
        node_name << node_count;

        if (added_nodes.find(current_depth-1) != added_nodes.end()) {
            std::stringstream previous_name;
            previous_name << added_nodes[current_depth-1];
            parse_data_ += "    " + previous_name.str();
            parse_data_ += " -- " + node_name.str();
        } else
            parse_data_ += "    " + node_name.str();

        parse_data_ += ";\n    " + node_name.str() + " [label= \"{"
                    +(node.get_name() == "/" ? graph_name_ : node.get_name());


        std::string fillcolor("[fillcolor =");

        auto current_core(node.get_core());

        if (!current_core)
            fillcolor += " \"#FFFFFF\"";

        else {
            switch(current_core->get_type()) {
                case Core::CAMERA:
                    fillcolor += " \"#AAFFAA\"";
                    break;
                case Core::LIGHT:
                    fillcolor += " \"#FFDD55\"";
                    break;
                case Core::SCREEN:
                    fillcolor += " \"#55DDFF\"";
                    break;
                case Core::GEOMETRY: {
                    auto geometry_core(
                                 reinterpret_cast<GeometryCore*>(current_core));
                    fillcolor += " \"#EEEEEE\"";
                    parse_data_ +=  "| geometry: "
                                + geometry_core->get_geometry()
                                +   "| material: "
                                + geometry_core->get_material();
                } break;

                default:;
            }
        }

        fillcolor += "]";

        parse_data_ += "}\"]" + std::string(" [shape = record]")
                    + " [style=filled] ";

        parse_data_ += fillcolor + ";\n";

        added_nodes[current_depth] =  node_count;
        ++node_count;
        node_name.str("");
    }

    parse_data_ += "} \n";
}

////////////////////////////////////////////////////////////////////////////////

void DotGenerator::
save(std::string const& path_to_file) const {

    std::fstream file;
    file.open(path_to_file + graph_name_ + ".gv", std::fstream::out);

    if (file.good()) {
        file.write(parse_data_.c_str(), parse_data_.size());
        file.close();
    } else {
        DEBUG("Failed to save dot graph: Failed to open file \"%s\"",
              (path_to_file + graph_name_ + ".gv").c_str());
    }
}

////////////////////////////////////////////////////////////////////////////////

}
