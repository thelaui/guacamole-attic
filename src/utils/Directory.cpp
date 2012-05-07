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
/// \brief A simple directory reader to get the members of a directory.
////////////////////////////////////////////////////////////////////////////////

// class header
#include "utils/Directory.hpp"

// guacamole headers
#include "utils/PathParser.hpp"
#include "utils/debug.hpp"

// external headers
#include <iostream>
#include <dirent.h>

namespace gua {

////////////////////////////////////////////////////////////////////////////////

Directory::
Directory():
    path_name_(""),
    content_(""),
    is_loaded_(false) {}

////////////////////////////////////////////////////////////////////////////////

Directory::
Directory(std::string const& path_name):
    path_name_(path_name),
    content_(""),
    is_loaded_(false) {

        PathParser path_parser;
        path_parser.parse(path_name_);
        if (!path_parser.path_is_finished_by_slash())
            path_name_ += "/";
    }

////////////////////////////////////////////////////////////////////////////////

bool Directory::
is_valid() const {

    return opendir(path_name_.c_str());
}

////////////////////////////////////////////////////////////////////////////////

std::string const& Directory::
get_content() const {

    if (is_loaded_)
        return content_;

    is_loaded_ = true;

    DIR* directory;
    directory = opendir(path_name_.c_str());

    if(!directory) {
        WARNING("Cannot access directory \"%s\"", path_name_.c_str());
        return content_;
    }

    dirent* entry(readdir(directory));

    while(entry){
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            content_ += entry->d_name + std::string(" ");
        entry = readdir(directory);
    }

    closedir(directory);

    return content_;
}

////////////////////////////////////////////////////////////////////////////////

std::string const& Directory::
get_directory_name() const{

    return path_name_;
}

////////////////////////////////////////////////////////////////////////////////

}

