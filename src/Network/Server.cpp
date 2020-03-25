#include "Server.h"

void FTPServer::InitServer(ServerOptions options) {
    this->options = options;

    this->InitCommandServer();
    this->InitDataServer();
}

void FTPServer::InitCommandServer() {
    this->cmdFD = this->CreateSocket();

    while (true) {
        FTPRequest req = this->AcceptMessage(this->cmdFD);

        ThreadData tdata;

        pthread_attr_init(&tdata.attrs);
        if (pthread_create(&tdata.id, &tdata.attrs, this->ManageRequest, (void *)&req) != 0) {
            throw runtime_error("Creating a new thread: failed");
        }
    }
}


void FTPServer::InitDataServer() {
    
}


/**
 * Creation socket
 */
int FTPServer::CreateSocket() {
    // Creating socket file descriptor
    int serverFileDescriptor;
    if ((serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        throw runtime_error("Creating socket file descriptor: failed");
    }

    // Reusing socket after program exit
    int reuse = 1;
    setsockopt(serverFileDescriptor, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // Binding on port which setted in options
    sockaddr_in address = (struct sockaddr_in) {
        AF_INET,
        htons(this->options.cmd_port),
        (struct in_addr){INADDR_ANY}
    };

    if (bind(serverFileDescriptor, (sockaddr *)&address, sizeof(sockaddr)) < 0) {
        throw runtime_error("Attaching socket to the port " + to_string(this->options.cmd_port) + ": failed");
    }
    
    // Listening incoming requests
    if (listen(serverFileDescriptor, this->options.connections_queue) < 0) {
        throw runtime_error("Listening on socket: failed");
    }

    cout << "Command connection started on port " << this->options.cmd_port << endl;
    return serverFileDescriptor;
}

/**
 * Accepting user message from file descriptor
 */
FTPRequest FTPServer::AcceptMessage(int listenFileDescriptor) {
    sockaddr_in clientAddress;
    socklen_t addrlen = sizeof(clientAddress);

    int acceptedMessageDesc = accept(listenFileDescriptor, (sockaddr *)&clientAddress, &addrlen);
    if (acceptedMessageDesc < 0) {
        throw runtime_error("Accepted message: failed");
    }
    return FTPRequest{ acceptedMessageDesc, clientAddress };
}

/**
 * Request manager
 * @param int connection desctiptor
 */
void * FTPServer::ManageRequest(void *requestProto) {
    FTPRequest request = *(FTPRequest *)requestProto;

    cout << request.socket_desc << endl;
    cout << request.client.sin_port << endl;

    // Sending welcome message to client
    char buffer[MAX_BUFFER_SIZE] = { 0 };
    // FTPResponse response(request);
    // response.Prepare(StatusCodes::SERVICE_READY, { "Привет" }, buffer);
    // response.Send();

    write(request.socket_desc, buffer, strlen(buffer));
    pthread_exit(0);
}