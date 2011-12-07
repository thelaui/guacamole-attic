#include "include/utils/PathParser.hpp"

#include <iostream>

int main() {
    PathParser parser("/");
    auto parsed_strings(parser.get_parsed_path());

    for (auto string : parsed_strings)
        std::cout << string << std::endl;

    return 0;
}
