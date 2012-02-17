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
/// \brief A simple file reader to get data out of text files.
////////////////////////////////////////////////////////////////////////////////

#include "utils/TextFile.hpp"

#include <sstream>
#include <fstream>

#include "utils/debug.hpp"

namespace gua {

TextFile::TextFile():
    file_name_(""),
    content_(""),
    is_loaded_(false) {}

TextFile::TextFile(std::string const& file_name):
    file_name_(file_name),
    content_(""),
    is_loaded_(false) {}

bool TextFile::is_valid() const {
    std::ifstream file(file_name_.c_str());

    if (file.fail())
        return false;

    file.close();
    return true;
}

std::string const& TextFile::get_content() const{
    if (is_loaded_)
        return content_;

    is_loaded_ = true;

    std::ifstream ifs(file_name_.c_str());
    if(!ifs) {
        WARNING("Cannot open file \"%s\"", file_name_.c_str());
        return content_;
    }

    std::stringstream oss;
    oss << ifs.rdbuf();

    if(!ifs && !ifs.eof()) {
        WARNING("Error reading file \"%s\"", file_name_.c_str());
        return content_;
    }

    content_ = std::string(oss.str());
    return content_;
}

std::string const& TextFile::get_file_name() const{
    return file_name_;
}

}



