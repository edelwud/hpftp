#pragma once

#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <functional>
#include <exception>

#include <unistd.h>
#include <csignal>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <netinet/in.h>

#include <arpa/inet.h>
#include <ctime>

#include <pthread.h>
#include <thread>
#include <future>

#include <client/request.h>
#include <client/response.h>
#include <client/status.h>

#include <logger/logger.h>

#include <executor/executor.h>

#include <exceptions/not_logged.h>
#include <exceptions/no_data_connection.h>
#include <exceptions/undefined_command.h>

#define MAX_BINARY_SIZE 1000

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
    static void ReceiveBinary(char buffer[MAX_BINARY_SIZE]);
    static void CloseDataServer();

    static int CreateSocket(int port, int connectionsQueue);
    void InitServer(ServerOptions options);
};