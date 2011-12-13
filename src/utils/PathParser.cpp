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
/// \brief A simple parser to get data out of paths.
////////////////////////////////////////////////////////////////////////////////

#include "include/utils/PathParser.hpp"

#include "include/utils/debug.hpp"

#include <sstream>

PathParser::PathParser():
    parsed_path_(),
    finished_by_slash_(false) {}

void PathParser::parse(std::string path) {
    if (path.length() > 0) {
            parsed_path_.clear();
        unsigned start(0);
        if (path[0] == '/') {
            parsed_path_.push_back("/");
            start = 1;
        }

        if (path[path.length()-1] == '/')
            finished_by_slash_ = true;

        std::stringstream stream;
        for (unsigned i(start); i < path.length(); ++i) {
            if (path[i] != '/') {
                stream << path[i];
            } else {
                parsed_path_.push_back(stream.str());
                stream.str("");
            }
        }

        if (stream.str().size() > 0) {
            parsed_path_.push_back(stream.str());
            stream.str("");
        }

    } else {
        ERROR("Path names must have at least one character!");
    }
}

std::vector<std::string> const& PathParser::get_parsed_path() const {
    return parsed_path_;
}

bool PathParser::path_is_finished_by_slash() const {
    return finished_by_slash_;
}
