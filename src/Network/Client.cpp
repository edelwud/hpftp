#include "Client.h"

/**
 * Reading and parsing client command
 */ 
FTPClient::Contract FTPClient::Read() {
    char buffer[MAX_BUFFER_SIZE] = { 0 };

    if (read(this->socketDesc, buffer, MAX_BUFFER_SIZE) < 0) {
        throw runtime_error("Unable to read message from client");
    }

    string commandBuffer(buffer);
    regex commandParser("^([A-Za-z]+)(?: +(.+))?");
    std::smatch match;

    if (!regex_match(commandBuffer, match, commandParser)) {
        throw runtime_error("Unable to search readed string");
    }

    if (match.size() == 0) {
        throw logic_error("Readed command not specificed");
    }

    string command = match.str(1);
    for_each(command.begin(), command.end(), [](char &element){ element = toupper(element); });
    
    if (FTPCommandListMap.find(command) == FTPCommandListMap.end()) {
        throw logic_error("Cannot identify client command");
    }
    return { FTPCommandListMap[command], match.str(2) };
}