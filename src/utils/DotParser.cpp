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
/// \brief A utility class to generate DOT-files from a SceneGraph.
////////////////////////////////////////////////////////////////////////////////

#include "include/utils/DotParser.hpp"

#include "include/scenegraph/SceneGraph.hpp"
#include "include/scenegraph/Iterator.hpp"

#include <fstream>
#include <map>

DotParser::DotParser():
    parse_data_() {}

void DotParser::parse_graph(SceneGraph const* graph, std::string const& name) {
    parse_data_ += "graph " + name + " { \n";

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

        parse_data_ += ";\n    " + node_name.str() + " [label="
                    + (node.get_name() == "/" ? "root" : node.get_name())
                    + "]" + ";\n";

        added_nodes[current_depth] =  node_count;
        ++node_count;
        node_name.str("");
    }

    parse_data_ += "} \n";
}

void DotParser::save_to_file(std::string const& file_name) const {
    std::fstream file;
    file.open(file_name, std::fstream::out);
    file.write(parse_data_.c_str(), parse_data_.size());
    file.close();
}
