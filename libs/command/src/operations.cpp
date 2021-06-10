#include <operations.h>

#include <iterator>
#include <regex>

std::string Operations::join(std::vector<std::string> vector, const std::string& delimiter) {
    std::ostringstream imploded;
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::string>(imploded, delimiter.c_str()));
    std::string implodedString = imploded.str();
    return implodedString.substr(0, implodedString.size() - delimiter.size());;
}

std::vector<std::string> Operations::split(const std::string& argsString, const std::string& delimiter) {
    std::regex regexz(delimiter + "+" + delimiter + "?");
    std::vector<std::string> list(std::sregex_token_iterator(argsString.begin(), argsString.end(), regexz, -1),
                                  std::sregex_token_iterator());
    return list;
}

std::string Operations::trim(std::string message) {
    message.erase(0, message.find_first_not_of(' '));
    message.erase(message.find_last_not_of(' ') + 1);
    return message;
}
