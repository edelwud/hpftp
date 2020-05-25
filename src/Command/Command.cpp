#include "Command.h"

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch) && ch != '\n';
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch) && ch != '\n';
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

/**
 * Unpack
 * Client input parser with regular expressions usage
 * @param data inputted string
 * @return FTP command, args
 */
pair<FTPCommandList, string> FTPCommand::Unpack(string data) {
    trim(data);
    regex commandParser("([A-Za-z]+)(?: +(.+))?");
    smatch match;

    if (!regex_match(data, match, commandParser)) {
        throw UndefinedCommand();
    }

    if (match.empty()) {
        throw UndefinedCommand();
    }

    string command = match.str(1);
    for_each(command.begin(), command.end(), [](char &element){ element = toupper(element); });
    
    if (FTPCommandListMap.find(command) == FTPCommandListMap.end()) {
        throw UndefinedCommand();
    }

    return { FTPCommandListMap[command], match.str(2) };
}

/**
 * Packing FTP command into string
 * @param code FTP code defined in StatusCodes
 * @param argument command argument
 * @return result string
 */
string FTPCommand::Pack(StatusCodes code, const string& argument) {
    string result = to_string((int)code);
    result += " ";
    result += argument;
    return result;
}

/**
 * Get command
 * Getting stringify command
 * @param command
 * @return optional string
 */
string FTPCommand::GetCommand(FTPCommandList command) {
    for (auto [commandStringify, reservedCommand] : FTPCommandListMap) {
        if (reservedCommand == command) {
            return commandStringify;
        }
    }
    return {};
}

vector<string> FTPCommand::ArgumentParse(string arguments) {
    vector<string> parsed;

    string delimiter = " ";

    size_t pos = 0;
    string token;
    while ((pos = arguments.find(delimiter)) != std::string::npos) {
        token = arguments.substr(0, pos);
        if (!token.empty())
            parsed.push_back(token);
        arguments.erase(0, pos + delimiter.length());
    }

    if (!arguments.empty())
        parsed.push_back(arguments);

    return parsed;
}
