#pragma once 

#include <string>
#include <vector>
#include <regex>
#include <functional>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#include "../Command/Command.h"

using namespace std;


class FTPClient {
    int socketDesc;
    sockaddr_in client;
public:
    using Contract = tuple<FTPCommandList, string>;

    FTPClient(int descriptor, sockaddr_in client) : socketDesc(descriptor), client(client) {};

    int GetClientDescriptor();
    string GetClientAddress();
    string GetClientPort();

    Contract Read();
};