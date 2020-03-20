#ifndef REQUEST
#define REQUEST

#include <arpa/inet.h>

using namespace std;

struct FTPRequest {
    int socket_desc;
    sockaddr_in client;
};

#endif
