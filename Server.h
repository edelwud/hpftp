#ifndef SERVER
#define SERVER

#include <string>
#include <functional>
#include <map>

#include "Command.h"

using namespace std;

struct ServerOptions {
    unsigned int threads = 1;
    unsigned int cmd_port = 21;
    unsigned int data_port = 8080;
};

struct FTPServerRequest {
    FTPCommandReader command;
    string body;
};

struct FTPServerResponse {
    FTPCommandReader command;
    string body;
};

class FTPServer {
private:
    map<FTPCommandList, function<void(void)>> handlerList;
    ServerOptions options;

    void InitCommandServer();
    void InitDataServer();
public:
    void InitServer(ServerOptions options);
    void ShutdownServer();
    unsigned int AddRequestHandler(function<void(FTPServerRequest, FTPServerResponse)> handler);
    void RemoveRequestHandler(unsigned int handlerId);
};

#endif