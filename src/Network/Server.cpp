#include "Server.h"

/**
 * Initialization of FTP server
 */
void FTPServer::InitServer(ServerOptions options) {
    this->options = options;

    // thread commandThread([this](){ this->InitCommandServer(); });
    // thread dataThread([this](){ this->InitCommandServer(); });
    // commandThread.join();
    // dataThread.join();

    this->InitCommandServer();
}

/** 
 * Creating and responsing command socket
 */
void FTPServer::InitCommandServer() try {
    this->cmdFD = this->CreateSocket(this->options.cmd_port);
    Logger::Info("Command server binded on port " + to_string(this->options.cmd_port));

    while (true) {
        // Waiting for new client
        FTPClient request = this->AcceptMessage(this->cmdFD);
        Logger::Info("Connection accepted, address");

        // Execution of async request manager
        async(launch::async, this->ManageRequest, request);
    }
} catch(runtime_error &error) {
    Logger::Error(error.what());
}

/**
 * Creating and responsing data socket
 */
void FTPServer::InitDataServer() {
    
}

/**
 * Creation socket
 */
int FTPServer::CreateSocket(int port) {
    Logger::Progress progress = Logger::CreateTask("Creating socket", 3);

    // Creating socket file descriptor
    int serverFileDescriptor;
    if ((serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        throw runtime_error("Creating socket file descriptor: failed");
    }
    progress("creating socket file descriptor");

    // Reusing socket after program exit
    int reuse = 1;
    setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // Binding on port which setted in options
    sockaddr_in address{
        AF_INET,
        htons(port),
        (struct in_addr){INADDR_ANY}
    };

    if (bind(serverFileDescriptor, (sockaddr *)&address, sizeof(sockaddr)) < 0) {
        throw runtime_error("Attaching socket to the port " + to_string(port) + ": failed");
    }
    progress("binding socket port options");
    
    // Listening incoming requests
    if (listen(serverFileDescriptor, this->options.connections_queue) < 0) {
        throw runtime_error("Listening on socket: failed");
    }
    progress("listening port");

    return serverFileDescriptor;
}

/**
 * Accepting user message from file descriptor
 */
FTPClient FTPServer::AcceptMessage(int listenFileDescriptor) {
    sockaddr_in clientAddress;
    socklen_t addrlen = sizeof(clientAddress);
    int acceptedMessageDesc = accept(listenFileDescriptor, (sockaddr *)&clientAddress, &addrlen);
    if (acceptedMessageDesc < 0) {
        throw runtime_error("Accepted message: failed");
    }
    return FTPClient{ acceptedMessageDesc, clientAddress };
}

/**
 * Request manager
 * @param int connection desctiptor
 */
void FTPServer::ManageRequest(FTPClient request) try {
    auto [code, cmd] = request.Read();
    
    string commandStringify = FTPCommandReader::GetCommand(code).value_or("");

    Logger::Info("Client sent commmand " + commandStringify 
        + (cmd.size() ? " with operand " + cmd : " with no operand"));

} catch(exception &e) { Logger::Error(e.what()); }