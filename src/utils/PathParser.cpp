#include "include/utils/PathParser.hpp"

#include "include/utils/debug.hpp"

#include <sstream>

PathParser::PathParser():
    parsed_path_(),
    finished_by_slash_(false) {}

void PathParser::parse(std::string path) {
    if (path.length() > 0) {
            parsed_path_.clear();
        unsigned start(0);
        if (path[0] == '/') {
            parsed_path_.push_back("/");
            start = 1;
        }

        if (path[path.length()-1] == '/')
            finished_by_slash_ = true;

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

bool PathParser::path_is_finished_by_slash() const {
    return finished_by_slash_;
}
