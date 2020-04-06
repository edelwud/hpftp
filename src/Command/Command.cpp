#include "Command.h"

FTPCommandList FTPCommandReader::Unpack(char data[MAX_BUFFER_SIZE]) {
    
}

optional<string> FTPCommandReader::GetCommand(FTPCommandList command) {
    for (auto [commandStringify, reservedCommand] : FTPCommandListMap) {
        if (reservedCommand == command) {
            return commandStringify;
        }
    }
    return {};
}