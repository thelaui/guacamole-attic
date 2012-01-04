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

namespace gua {

PathParser::PathParser():
    parsed_path_(),
    finished_by_slash_(false) {}

void PathParser::parse(std::string path) {

    if (path.length() > 0) {
        parsed_path_.clear();
        unsigned start(0);
//        unsigned last_slash_occur(-1);
        if (path[0] == '/') {
            parsed_path_.push_back("/");
            start = 1;
//           last_slash_occur = 0;
        }

        if (path[path.length()-1] == '/')
            finished_by_slash_ = true;

        std::string string;
        for (unsigned i(start); i < path.length(); ++i) {
            if (path[i] != '/') {
                string += path[i];
            } else {
                parsed_path_.push_back(string);
                string = "";
            }
        }

        if (string.size() > 0) {
            parsed_path_.push_back(string);
            string = "";
        }

//        unsigned current_string_length(0);
//        for (unsigned i(start); i < path.length(); ++i) {
//            if (path[i] != '/') {
//                ++current_string_length;
//            } else {
//                DEBUG("%c", path[i]);
//                parsed_path_.push_back(std::string(path, last_slash_occur+1, last_slash_occur+current_string_length));
//                last_slash_occur = i;
//                current_string_length = 0;
//            }
//        }

    } else {
        ERROR("Path names must have at least one character!");
    }
}

std::string PathParser::get_path(bool ignore_last_entry) const {
    std::string path;

    for (auto entry(parsed_path_.begin()); entry != parsed_path_.end(); ++entry) {
        if (entry == parsed_path_.end()-1) {
            if (ignore_last_entry)
                break;
            if (!path_is_finished_by_slash()) {
                path += (*entry);
                break;
            }
        }
        path += (*entry) + std::string("/");
    }

    return path;
}

std::vector<std::string> const& PathParser::get_parsed_path() const {
    return parsed_path_;
}

bool PathParser::path_is_finished_by_slash() const {
    return finished_by_slash_;
}

void PathParser::make_absolute(std::string const& path_from_cwd) {
    PathParser current_working_dir;
    current_working_dir.parse(path_from_cwd);

    while (parsed_path_.front() == "..") {
        parsed_path_.erase(parsed_path_.begin());
        current_working_dir.parsed_path_.erase(current_working_dir.parsed_path_.end()-1);
    }

    current_working_dir.parsed_path_.insert(current_working_dir.parsed_path_.end(),
                                            parsed_path_.begin(), parsed_path_.end());

    parsed_path_ = current_working_dir.parsed_path_;
}

}
