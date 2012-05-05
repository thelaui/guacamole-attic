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
/// \brief Declaration of the RenderMask class.
////////////////////////////////////////////////////////////////////////////////

#ifndef GUA_RENDER_MASK_HPP
#define GUA_RENDER_MASK_HPP

// external headers
#include <string>
#include <vector>
#include <set>

namespace gua {

////////////////////////////////////////////////////////////////////////////////
/// \brief RenderMasks are used to display only parts of a scene graph.
///
/// A RenderMask is a string like "floor & lights". This RenderMask will only
/// display nodes which are in both groups; "floor" and "lights" --- all other
/// nodes are discarded. If the mask is "floor | lights" all nodes which are in
/// one (or both) groups are shown. Supported operators are:
/// & --- and
/// | --- or
/// ! --- not
/// ( --- opening parenthesis
/// ) --- closing parenthesis
/// Whitespaces are ignored and all other characters are treated as group names.
////////////////////////////////////////////////////////////////////////////////
class RenderMask {
    public:

        ////////////////////////////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// This constructs an RenderMask.
        ///
        /// \param render_mask      The RenderMask's string representation.
        ////////////////////////////////////////////////////////////////////////
        RenderMask(std::string const& render_mask);

        ////////////////////////////////////////////////////////////////////////
        /// \brief Checks a given list of groups against this mask.
        ///
        /// \param groups           A set of groups.
        /// \return                 true, if the given list of groups is
        ///                         supported by this RenderMask.
        ////////////////////////////////////////////////////////////////////////
        bool check(std::set<std::string> const& groups) const;

    private:

        class BasicExpression {
            public:
                BasicExpression(std::string const& expression);

                bool check(std::set<std::string> const& groups) const;

            private:
                std::string remove_useless_brackets(
                                            std::string const& input) const;

                enum Operation { AND, OR, NOT, VALUE } type_;

                std::vector<BasicExpression> children_;
                std::string value_;

        } expression_;
};

}

#endif // GUA_RENDER_MASK_HPP

