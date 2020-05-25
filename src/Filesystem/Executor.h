#pragma once 

#include <iostream>
#include <iomanip>
#include <array>
#include <experimental/filesystem>

#include "../Command/Command.h"
#include "../Network/Client.h"
#include "../Network/Server.h"
#include "../Network/StatusCodes.h"

using namespace std;
namespace fs = std::experimental::filesystem;

class Executor {
    FTPClient& client;
    string currentPath;

    string exec(const char* cmd) {
        array<char, 128> buffer;
        string result;
        unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
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
        fs::current_path(path);
    };

    pair<StatusCodes, string> Command(FTPCommandList code, vector<string> arguments);

    void CWD(string path);
    void LIST();
    void USER(string username);
    void PASS(string password);
    void PASV();
    void RETR(string filename);
};