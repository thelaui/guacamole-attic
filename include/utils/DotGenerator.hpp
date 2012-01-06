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
/// \brief Declaration of the DotGenerator class.
////////////////////////////////////////////////////////////////////////////////

#ifndef DOT_GENERATOR_HPP
#define DOT_GENERATOR_HPP

#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class may be used to parse a path.
///
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class SceneGraph;

class DotGenerator {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs a DotGenerator
        ////////////////////////////////////////////////////////////////////////
        DotGenerator();

        ////////////////////////////////////////////////////////////////////////
        ///\brief Parses a graph.
        ///
        /// This function parses a SceneGraph and generates a graph in
        /// DOT-syntax.
        ///
        ///\param graph       The graph to be parsed.
        ///\param name        The name of the output graph.
        ////////////////////////////////////////////////////////////////////////
        void parse_graph(SceneGraph const* graph, std::string const& name);

        ////////////////////////////////////////////////////////////////////////
        ///\brief Saves a DOT-file
        ///
        /// This function saves the generated DOT-graph.
        ///
        ///\param file_name The name of the file the DOT-graph will be saved to.
        ///                 The ending has to be .gv or .dot.
        ////////////////////////////////////////////////////////////////////////
        void save_to_file(std::string const& file_name) const;

    private:

        std::string parse_data_, graph_name_;

};

}

#endif //DOT_GENERATOR_HPP

