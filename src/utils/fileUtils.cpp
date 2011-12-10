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

#include "include/utils/fileUtils.hpp"

#include <fstream>

namespace fileUtils {

    char* text_file_read(std::string const& file_name) {
        char* text = 0;

        FILE *file = fopen(file_name.c_str(), "rt");

        if (file != 0) {
            fseek(file, 0, SEEK_END);
            int count = ftell(file);
            rewind(file);

            if (count > 0) {
                text = (char*)malloc(sizeof(char) * (count + 1));
                count = fread(text, sizeof(char), count, file);
                text[count] = '\0';
            }
            fclose(file);
        }

        return text;
    }

    bool file_exists( std::string const& file_name ) {
        std::ifstream fin(file_name.c_str());
        if (!fin.fail()) {
            fin.close();
            return true;
        }

        return false;
    }
}




