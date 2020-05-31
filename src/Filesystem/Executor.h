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
    string renameFrom;
    bool binary = false;

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
    bool exists(const fs::path& p, fs::file_status s = fs::file_status{}) {
        return fs::status_known(s) ? fs::exists(s) : fs::exists(p);
    }
public:
    explicit Executor(FTPClient& request, string path) : client(request) {
        this->client.currentPath = path;
        this->client.homeDir = path;
    };

    pair<StatusCodes, string> Command(FTPCommandList code, string argument);

    void CWD(string path);
    void LIST();
    void USER(string username);
    void PASS(string password);
    void PASV();
    void RETR(string filename);
};