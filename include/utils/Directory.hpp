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
/// \brief Declaration of the Directory class.
////////////////////////////////////////////////////////////////////////////////

#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>

////////////////////////////////////////////////////////////////////////////////
/// \brief This class is used to read the contents of a directory.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

class Directory {

    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a Directory without a path.
        ////////////////////////////////////////////////////////////////////////
        Directory();

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs a Directory with a path.
        ///
        /// \param path_name The path to the directory to be read.
        ////////////////////////////////////////////////////////////////////////
        Directory(std::string const& path_name);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns if the given path to the directory is valid.
        ///
        /// \return The validity of the path.
        ////////////////////////////////////////////////////////////////////////
        bool is_valid() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the given directory's content.
        ///
        /// \return The given directory's content.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_content() const;

        ////////////////////////////////////////////////////////////////////////
        /// \brief Returns the given directory's name.
        ///
        /// \return The given directory's name.
        ////////////////////////////////////////////////////////////////////////
        std::string const& get_directory_name() const;

    private:
        std::string path_name_;
        mutable std::string content_;

        mutable bool is_loaded_;
};

}

#endif // DIRECTORY_HPP




