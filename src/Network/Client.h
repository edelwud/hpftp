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

using namespace std;


class FTPClient {
    string username = "";

    int socketDesc;
    sockaddr_in client;

    vector<pair<string, string>> users = {
            { "edelwud", "123" }
    };
public:
    using Contract = tuple<FTPCommandList, string>;

    FTPClient(int descriptor, sockaddr_in client) : socketDesc(descriptor), client(client) {};

    int GetClientDescriptor() const;
    string GetClientAddress();
    string GetClientPort() const;

    void SetAuthorized(string username);
    string IsAuthorized() const;
    bool Authorize(string username, string password);

    Contract Read() const;
};