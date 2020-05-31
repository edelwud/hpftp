#pragma once 

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <algorithm>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include "../Command/Command.h"
#include "../Exception/AlreadyDeclared.h"

using namespace std;

class FTPClient {
    string username = "";
    string password = "";
    bool authorized = false;

    int socketDesc;
    sockaddr_in client;

    map<string, string> users = {
            { "edelwud", "123" }
    };
public:
    string homeDir;
    string currentPath;

    using Contract = tuple<FTPCommandList, string>;

    FTPClient(int descriptor, sockaddr_in client) : socketDesc(descriptor), client(client) {};

    int GetClientDescriptor() const;
    string GetClientAddress();
    string GetClientPort() const;

    bool IsAuthorized() const;

    void Authorize();
    void SetUsername(string username);
    void SetPassword(string password);

    Contract Read() const;
};