#ifndef PATH_PARSER_HPP
#define PATH_PARSER_HPP

#include <vector>
#include <string>

class PathParser {
    public:
        PathParser();

        void parse(std::string path);
        std::vector<std::string> const& get_parsed_path() const;
        bool path_is_finished_by_slash() const;

    private:
        std::vector<std::string> parsed_path_;
        bool finished_by_slash_;
};

#endif //PATH_PARSER_HPP
