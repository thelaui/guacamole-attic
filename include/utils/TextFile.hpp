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
/// \brief Declaration of the TextFile class.
////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTFILE_HPP
#define TEXTFILE_HPP

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to read text files.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class TextFile {

    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a TextFile without a file.
        ////////////////////////////////////////////////////////////////////////
        TextFile();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a TextFile with a file.
        ///
        /// \param file_name The file to be read.
        ////////////////////////////////////////////////////////////////////////
        TextFile(std::string const& file_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns if the given file is valid.
        ///
        /// \return The validity of the file.
        ////////////////////////////////////////////////////////////////////////
        bool is_valid() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the given file's content.
        ///
        /// \return The given file's content.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_content() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the given file's name.
        ///
        /// \return The given file's name.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_file_name() const;

    private:
        std::string file_name_;
        mutable std::string content_;

        mutable bool is_loaded_;
};

}

#endif // TEXTFILE_HPP



