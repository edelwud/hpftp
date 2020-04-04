#ifndef SERVER
#define SERVER

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

#include "Request.h"
#include "Response.h"
#include "StatusCodes.h"
#include "../Logger.h"

#define MAX_BUFFER_SIZE 4096

using namespace std;

struct ServerOptions {
    unsigned int connections_queue = 1;
    unsigned int cmd_port = 21;
    unsigned int data_port = 8080;
};

class FTPServer {
private:
    ServerOptions options;
    int cmdFD;
    int dataFD;

    void InitCommandServer();
    void InitDataServer();
    
    int CreateSocket(int port);
    static FTPRequest AcceptMessage(int listenFileDesc);
    static void ManageRequest(FTPRequest request);
public:
    void InitServer(ServerOptions options);
    void ShutdownServer();
    unsigned int AddRequestHandler(function<void(FTPRequest, FTPResponse)> handler);
    void RemoveRequestHandler(unsigned int handler_id);
};

#endif