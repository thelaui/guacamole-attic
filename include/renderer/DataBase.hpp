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
/// \brief A database for accessing data.
////////////////////////////////////////////////////////////////////////////////

#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include <memory>
#include <string>
#include <map>

template <typename T>

class DataBase {
    public:
        void add( std::string const& id, std::shared_ptr<T> date ) {
            data_.insert(std::make_pair(id, date));
        }

        bool is_supported( std::string const& id ) const {
            return data_.find(id) != data_.end();
        }

        std::shared_ptr<T> get( std::string const& id ) {
            auto result(data_.find(id));
            if (result == data_.end())
                return NULL;

            return result->second;
        }

    private:
        std::map<std::string, std::shared_ptr<T>> data_;
};

#endif // DATA_BASE_HPP
