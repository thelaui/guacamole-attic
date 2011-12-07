#ifndef PATH_PARSER_HPP
#define PATH_PARSER_HPP

#include <vector>
#include <string>

class PathParser {
    public:
        PathParser(std::string path);

        std::vector<std::string> const& get_parsed_path() const;

    private:
        std::vector<std::string> parsed_path_;
};

#endif //PATH_PARSER_HPP
