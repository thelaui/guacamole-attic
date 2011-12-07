#include "include/utils/PathParser.hpp"

#include <sstream>

PathParser::PathParser(std::string path) {
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
    }
}

std::vector<std::string> const& PathParser::get_parsed_path() const {
    return parsed_path_;
}

