#pragma once 

#include <iostream>
#include <experimental/filesystem>

#include "../Command/Command.h"
#include "../Network/StatusCodes.h"

using namespace std;
namespace fs = std::experimental::filesystem;

class Executor {
public:
    static pair<StatusCodes, string> Command(FTPCommandList code, vector<string> arguments);
};