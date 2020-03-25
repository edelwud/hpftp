#ifndef REQUEST
#define REQUEST

#include <functional>
#include <arpa/inet.h>
#include "../Command/Command.h"

using namespace std;


class FTPRequest {
public:
    int socket_desc;
    sockaddr_in client;
    void Parse(function<void(FTPCommandList, int, sockaddr_in)> handler);
};

#endif
