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
/// \brief A class storing geometry data.
////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTFILE_HPP
#define TEXTFILE_HPP

#include <string>

class TextFile {

    public:
        TextFile();
        TextFile(std::string const& file_name);

        bool is_valid() const;

        std::string const& get_content();
        std::string const& get_file_name();

    private:
        std::string file_name_;
        std::string content_;

        bool is_loaded_;
};

#endif // TEXTFILE_HPP



