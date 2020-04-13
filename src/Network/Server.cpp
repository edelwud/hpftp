#include "Server.h"

/**
 * Initialization of FTP server
 */
void FTPServer::InitServer(ServerOptions options) {
    this->options = options;
    this->InitCommandServer();
}

/** 
 * Creating and responsing command socket
 */
void FTPServer::InitCommandServer() try {
    this->cmdFD = this->CreateSocket(this->options.cmdPort);
    Logger::Print(Logger::Levels::INFO, "Command server binded on port " + to_string(this->options.cmdPort));

    while (true) {
        // Waiting for new client
        FTPClient request = this->AcceptMessage(this->cmdFD);
        Logger::Print(Logger::Levels::INFO, "Connection accepted, address: " + request.GetClientAddress() + ":" + request.GetClientPort());
        
        // Execution of async request manager
        thread manager([this](FTPClient &request){ this->ManageRequest(request); }, ref(request));
        manager.detach();
    }
} catch(runtime_error &error) {
    Logger::Print(Logger::Levels::ERROR, error.what());
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
    Logger::Contract progress = Logger::CreateTask("Creating socket", 3);

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
FTPClient FTPServer::AcceptMessage(int listenConnDescriptor) {
    sockaddr_in clientAddress;
    socklen_t addrlen = sizeof(clientAddress);
    int acceptedMessageDesc = accept(listenConnDescriptor, (sockaddr *)&clientAddress, &addrlen);
    if (acceptedMessageDesc < 0) {
        throw runtime_error("Accepted message: failed");
    }
    return FTPClient{ acceptedMessageDesc, clientAddress };
}

/**
 * Request manager
 * @param request connection desctiptor
 */
void FTPServer::ManageRequest(FTPClient &request) {
    auto logger = Logger::SetPrefix(request.GetClientAddress() + ":" + request.GetClientPort());
    while (true) try {
        auto [code, cmd] = request.Read();
        string commandStringify = FTPCommand::GetCommand(code).value_or("NOOP");

        logger(Logger::Levels::INFO, "Client sent commmand " + commandStringify 
            + (cmd.size() ? " with operand " + cmd : " with no operand"));

    } catch(const logic_error& e) {
        logger(Logger::Levels::ERROR, e.what());
    } catch(const runtime_error& e) {
        logger(Logger::Levels::INFO, "Lost connection");
        return;
    }
}