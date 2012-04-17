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
/// \brief Declaration of the RenderMask class.
////////////////////////////////////////////////////////////////////////////////

#ifndef RENDER_MASK_HPP
#define RENDER_MASK_HPP

#include <string>
#include <vector>
#include <set>

namespace gua {

class RenderMask {
    public:

        ////////////////////////////////////////////////////////////////////////
        ///\brief Constructor.
        ///
        /// This constructs an RenderMask.
        ////////////////////////////////////////////////////////////////////////
        RenderMask(std::string const& render_mask);

        bool check(std::set<std::string> const& groups) const;

    private:

        class BasicExpression {
            public:
                BasicExpression(std::string const& expression);

                bool check(std::set<std::string> const& groups) const;

            private:
                std::string remove_useless_brackets(std::string const& input) const;

                enum Operation { AND, OR, NOT, VALUE } type_;

                std::vector<BasicExpression> children_;
                std::string value_;

        } expression_;
};

}

#endif // RENDER_MASK_HPP
