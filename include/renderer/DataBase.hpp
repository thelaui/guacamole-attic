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
/// \brief Declaration and implementation of the DataBase class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_DATA_BASE_HPP
#define GUA_DATA_BASE_HPP

#include <memory>
#include <string>
#include <map>

////////////////////////////////////////////////////////////////////////////////
/// \brief A database for accessing data.
///
/// It can store any type of Data. The data is mapped on strings, which then can
/// be used to access this data.
////////////////////////////////////////////////////////////////////////////////

namespace gua {

template <typename T>

class DataBase {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Adds a new entry to the data base.
        ///
        /// It can be accessed later with the get() method.
        ///
        /// \param id   The unique ID of this entry.
        /// \param date The newly added entry.
        ////////////////////////////////////////////////////////////////////////
        void add( std::string const& id, std::shared_ptr<T> date ) {
            data_.insert(std::make_pair(id, date));
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Check for existance of a ID.
        ///
        /// Returns true, if a entry with the given ID exists in the DataBase.
        ///
        /// \param id The ID to check for.
        /// \return   Whether the given ID is stored in the DataBase.
        ////////////////////////////////////////////////////////////////////////
        bool is_supported( std::string const& id ) const {
            return data_.find(id) != data_.end();
        }

        ////////////////////////////////////////////////////////////////////////
        /// \brief Gets an entry from the DataBase
        ///
        /// Returns a entry from the DataBase. It will return NULL if the entry
        /// in question does not exist.
        ///
        /// \param  id The ID of the entry.
        /// \return    A shared pointer to the data of the requested entry. NULL
        ///            if the entry does not exist.
        ////////////////////////////////////////////////////////////////////////
        std::shared_ptr<T> get( std::string const& id ) {
            auto result(data_.find(id));
            if (result == data_.end())
                return NULL;

            return result->second;
        }

    private:
        std::map<std::string, std::shared_ptr<T>> data_;
};

}

#endif // GUA_DATA_BASE_HPP
