#pragma once

#include <string>
#include <vector>
#include <regex>
#include <functional>
#include <algorithm>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include <command/command.h>
#include <client/request.h>
#include <exceptions/already_logged.h>

using namespace std;

class FTPClient {
    string username;
    string password;
    bool authorized = false;

    int socketDesc;
    sockaddr_in client;

    vector<pair<string, string>> users = {
            { "edelwud", "123" }
    };
public:
    using Contract = tuple<CommandList, string>;

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