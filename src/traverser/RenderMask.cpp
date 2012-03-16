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
/// \brief Implementation of the RenderMask class.
////////////////////////////////////////////////////////////////////////////////

#include "traverser/RenderMask.hpp"

#include "utils/debug.hpp"

#include <iostream>

namespace gua {

RenderMask::RenderMask(std::string const& render_mask):
    expression_(render_mask) {}

bool RenderMask::check(std::set<std::string> const& groups) const {
    return expression_.check(groups);
}

RenderMask::BasicExpression::BasicExpression(std::string const& expression):
    type_(VALUE),
    children_(),
    value_("") {

    int open_brackets(0);
    std::string current_expression;
    std::string expr(remove_useless_brackets(expression));
    std::vector<std::string> child_expressions;

    if (expr == "")
        return;

    for (unsigned i(0); i < expr.size(); ++i) {
        char c(expr[i]);

        switch (c) {
            case ' ': {

                break;
            } case '(': {
                ++open_brackets;

                current_expression += '(';

                break;
            } case ')': {
                --open_brackets;

                if (open_brackets < 0) {
                    WARNING("Failed to parse expression %s: Unexpected ) at %u", expr.c_str(), i);
                    return;
                } else if (open_brackets == 0 && current_expression != "") {
                    if (current_expression[current_expression.size()-1] == '(' || current_expression[current_expression.size()-1] == '!' ) {
                        WARNING("Failed to parse expression %s: Unexpected ) at %u", expr.c_str(), i);
                        return;
                    }

                    child_expressions.push_back(current_expression + ')');
                    current_expression = "";
                } else if (open_brackets > 0) {
                    current_expression += ')';
                }
                break;
            } case '&': {

                if (child_expressions.size() == 0 && current_expression == "") {
                    WARNING("Failed to parse expression %s: Unexpected & at %u", expr.c_str(), i);
                    return;
                } else if (open_brackets == 0) {
                    if (current_expression != "") {
                        child_expressions.push_back(current_expression);
                        current_expression = "";
                    }

                    if (type_ == OR) {
                        WARNING("Failed to parse expression %s: Unexpected & at %u. Don't mix & and | in one expression. Please use brackets!", expr.c_str(), i);
                        return;
                    }

                    type_ = AND;
                } else if (open_brackets > 0) {
                    current_expression += '&';
                }

                break;
            } case '|': {

                if (child_expressions.size() == 0 && current_expression == "") {
                    WARNING("Failed to parse expression %s: Unexpected | at %u", expr.c_str(), i);
                    return;
                } else if (open_brackets == 0) {
                    if (current_expression != "") {
                        child_expressions.push_back(current_expression);
                        current_expression = "";
                    }

                    if (type_ == AND) {
                        WARNING("Failed to parse expression %s: Unexpected | at %u. Don't mix & and | in one expression. Please use brackets!", expr.c_str(), i);
                        return;
                    }

                    type_ = OR;
                } else if (open_brackets > 0) {
                    current_expression += '|';
                }

                break;
            } case '!': {

                if (open_brackets == 0 && current_expression == "") {
                    current_expression += '!';
                } else if (open_brackets <= 0) {
                    WARNING("Failed to parse expression %s: Unexpected ! at %u.", expr.c_str(), i);
                    return;
                } else if (open_brackets > 0) {
                    current_expression += '!';
                }

                break;
            } default: {
                current_expression += c;

                break;
            }
        }
    }

    if (open_brackets > 0) {
        WARNING("Failed to parse expression %s: Expected ) at end of input.", expr.c_str());
        return;
    }

    if (current_expression != "")
        child_expressions.push_back(current_expression);

    if (child_expressions.size() == 1 && child_expressions[0][0] == '!') {
        if (child_expressions[0].size() == 1) {
            WARNING("Failed to parse expression %s.", expr.c_str());
            return;
        }

        type_ = NOT;
        children_.push_back(BasicExpression(child_expressions[0].substr(1)));

        return;
    }

    if (type_ == VALUE) {
        value_ = *child_expressions.begin();
        return;
    }

    for(auto& child: child_expressions) {
        children_.push_back(BasicExpression(child));
    }

}

bool RenderMask::BasicExpression::check(std::set<std::string> const& groups) const {
    switch (type_) {
        case AND: {
            for (auto& child: children_)
                if (!child.check(groups))
                    return false;
            return true;
        } case OR: {
            for (auto& child: children_)
                if (child.check(groups))
                    return true;
            return false;
        } case NOT: {
            return !children_.begin()->check(groups);
        } case VALUE: {
            if (value_ == "")
                return true;
            if (groups.size() == 0)
                return false;
            return groups.find(value_) != groups.end();
        }
    }
    return false;
}

std::string RenderMask::BasicExpression::remove_useless_brackets(std::string const& input) const {
    // remove leading and trailing corresponding brackets
    unsigned int leading_brackets(0);
    while (leading_brackets < input.size() && input[leading_brackets] == '(') {
        ++leading_brackets;
    }

    // count removable brackets
    if (leading_brackets > 0) {
        unsigned int removable_brackets(leading_brackets);
        unsigned int open_brackets(leading_brackets);

        for (unsigned i(leading_brackets); i<input.size()-leading_brackets; ++i) {
            if (input[i] == '(') {
                ++open_brackets;
            } else if (input[i] == ')') {
                --open_brackets;
                if (open_brackets < removable_brackets)
                    removable_brackets = open_brackets;
            }
        }

        return input.substr(removable_brackets, input.size()-2*removable_brackets);

    }

    return input;
}


}
