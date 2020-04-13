#pragma once

#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <functional>
#include <exception>

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <netinet/in.h>
#include <time.h>
  
#include <arpa/inet.h>   
#include <sys/time.h>

#include <pthread.h>
#include <thread>
#include <future>

#include "Client.h"
#include "Response.h"
#include "StatusCodes.h"
#include "../Command/Command.h"
#include "../Logger.h"

using namespace std;

struct ServerOptions {
    unsigned int connections_queue = 1;
    unsigned int cmdPort = 21;
    unsigned int dataPort = 8080;
};

class FTPServer {
private:
    ServerOptions options;
    int cmdFD;
    int dataFD;

    void InitCommandServer();
    void InitDataServer();
    
    int CreateSocket(int port);
    static FTPClient AcceptMessage(int listenFileDesc);
    static void ManageRequest(FTPClient &request);
public:
    void InitServer(ServerOptions options);
    void ShutdownServer();
    unsigned int AddClientHandler(function<void(FTPClient, FTPResponse)> handler);
    void RemoveClientHandler(unsigned int handler_id);
};