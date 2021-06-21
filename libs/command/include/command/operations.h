#pragma once

#include <iterator>
#include <sstream>
#include <vector>

namespace Operations {
    std::string join(std::vector<std::string> vector, const std::string &delimiter);
    std::vector<std::string> split(const std::string &argsString,
                                   const std::string &delimiter);
    std::string trim(std::string message);
}// namespace Operations