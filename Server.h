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
    unsigned int AddRequestHandler(FTPCommandList cmd, function<void(FTPServerResponse)> handler);
    void RemoveRequestHandler(unsigned int handlerId);
};

#endif