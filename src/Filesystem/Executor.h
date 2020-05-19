#pragma once 

#include <iostream>
#include <experimental/filesystem>

#include "../Command/Command.h"
#include "../Network/Response.h"
#include "../Network/StatusCodes.h"

using namespace std;
namespace fs = std::experimental::filesystem;

class Executor {
    FTPResponse& response;
    string currentPath;
public:
    explicit Executor(FTPResponse& res, string path) : response(res), currentPath(path) {};

    pair<StatusCodes, string> Command(FTPCommandList code, vector<string> arguments);


};