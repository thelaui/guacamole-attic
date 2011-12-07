#include "include/utils/PathParser.hpp"

#include "include/utils/debug.hpp"

#include <sstream>

PathParser::PathParser():
    parsed_path_() {}

void PathParser::parse(std::string path) {
    if (path.length() > 0) {

        unsigned start(0);
        if (path[0] == '/') {
            parsed_path_.push_back("/");
            start = 1;
        }

        std::stringstream stream;
        for (unsigned i(start); i < path.length(); ++i) {
            if (path[i] != '/') {
                stream << path[i];
            } else {
                parsed_path_.push_back(stream.str());
                stream.str("");
            }
        }

        if (stream.str().size() > 0) {
            parsed_path_.push_back(stream.str());
            stream.str("");
        }

    } else {
        ERROR("Path names must have at least one character!");
    }
}

std::vector<std::string> const& PathParser::get_parsed_path() const {
    return parsed_path_;
}

