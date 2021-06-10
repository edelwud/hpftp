#pragma once

#include <iostream>
#include <iomanip>
#include <array>
#include <filesystem>

#include <command/command.h>

#include <client/request.h>
#include <client/status.h>
#include <socket/server.h>

using namespace std;

class Executor {
    FTPClient& client;
    string currentPath;
    string renameFrom;

    string exec(string cmd) {
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
        if (!pipe) {
            throw runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
public:
    explicit Executor(FTPClient& request, string path) : client(request), currentPath(path) {
        filesystem::current_path(path);
    };

    pair<StatusCodes, string> Command(CommandList code, string argument);

    void CWD(string path);
    void LIST();
    void USER(string username);
    void PASS(string password);
    void PASV();
    void RETR(string filename);
};