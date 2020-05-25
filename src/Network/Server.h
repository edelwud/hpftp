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
#include "../Logger.h"
#include "../Command/Command.h"
#include "../Filesystem/Executor.h"

#include "../Exception/NotLogged.h"
#include "../Exception/NoDataConnection.h"
#include "../Exception/UndefinedCommand.h"

using namespace std;

struct ServerOptions {
    unsigned int connections_queue = 1;
    unsigned int cmdPort = 21;
    unsigned int dataPort = 8080;
};

class FTPServer {
private:
    ServerOptions options;
    int cmdFD{};

    void InitCommandServer();
    static void ManageRequest(FTPClient &request);
public:
    static FTPClient AcceptMessage(int listenFileDesc);

    static inline int dataFD{};
    static inline int dataPort{};
    static inline bool dataChannelInitialized = false;

    static void InitDataServer();
    static void SendBinary(string buffer);
    static void CloseDataServer();

    static int CreateSocket(int port, int connectionsQueue);
    void InitServer(ServerOptions options);
};