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
    this->cmdFD = CreateSocket(this->options.cmdPort, this->options.connections_queue);
    Logger::Print(Logger::Levels::INFO, "Command server binded on port " + to_string(this->options.cmdPort));

    while (true) {
        // Waiting for new client
        FTPClient request = FTPServer::AcceptMessage(this->cmdFD, true);
        Logger::Print(Logger::Levels::INFO, "Connection accepted, address: " + request.GetClientAddress() + ":" + request.GetClientPort());
        
        // Execution of async request manager
        thread manager([this](FTPClient &request){ FTPServer::ManageRequest(request); }, ref(request));
        manager.detach();
    }
} catch(runtime_error &error) {
    Logger::Print(Logger::Levels::ERROR, error.what());
}

/**
 * Creating and response data socket
 */
void FTPServer::InitDataServer() try {
    srand(time(0));
//    dataPort = rand() % (65536 - 40000) + 40000;
    dataPort = 50506;
    dataFD = CreateSocket(dataPort, 10);
    dataChannelInitialized = true;

    auto logger = Logger::SetPrefix("Datachannel");

    logger(Logger::Levels::INFO, "binded on port " + to_string(dataPort));
} catch(runtime_error &error) {
    Logger::Print(Logger::Levels::ERROR, error.what());
}

/**
 * Creation socket
 */
int FTPServer::CreateSocket(int port, int connectionsQueue) {
    Logger::Contract progress = Logger::CreateTask("Creating socket", 3);

    // Creating socket file descriptor
    int serverFileDescriptor;
    if ((serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        throw runtime_error("Creating socket descriptor: failed");
    }
    progress("creating socket descriptor");

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
    if (listen(serverFileDescriptor, connectionsQueue) < 0) {
        throw runtime_error("Listening on socket: failed");
    }
    progress("listening port");

    return serverFileDescriptor;
}

/**
 * Accepting user message from file descriptor
 */
FTPClient FTPServer::AcceptMessage(int listenConnDescriptor, bool blocking) {
    sockaddr_in clientAddress{};
    socklen_t addrlen = sizeof(clientAddress);
    int acceptedMessageDesc;
    if (!blocking) {
        acceptedMessageDesc = accept4(listenConnDescriptor, (sockaddr *)&clientAddress, &addrlen, SOCK_NONBLOCK);
        if (acceptedMessageDesc < 0) {
            throw runtime_error("Accepted message: failed");
        }
    } else {
        acceptedMessageDesc = accept(listenConnDescriptor, (sockaddr *)&clientAddress, &addrlen);
        if (acceptedMessageDesc < 0) {
            throw runtime_error("Accepted message: failed");
        }
    }
    return FTPClient{ acceptedMessageDesc, clientAddress };
}

/**
 * Request manager
 * @param request connection descriptor
 */
void FTPServer::ManageRequest(FTPClient &request) {
    auto logger = Logger::SetPrefix(request.GetClientAddress() + ":" + request.GetClientPort());
    string currentDir = "/home/user";

    FTPResponse response(request);
    Executor executor(request, currentDir);

    response.Send(StatusCodes::SERVICE_READY, "Welcome");
    while (true) try {
        auto tuple = request.Read();
        FTPCommandList requested = get<0>(tuple);
        string cmd = get<1>(tuple);

        if (requested == FTPCommandList::NOOP)
            continue;

        string commandStringify = FTPCommand::GetCommand(requested);

        if (!request.IsAuthorized()) {
            if (notLoggedAllowed.end() == notLoggedAllowed.find(commandStringify)) {
                throw NotLogged();
            }
        }

        logger(Logger::Levels::INFO, "Client sent command " + commandStringify
            + (!cmd.empty() ? " with operand " + cmd : " with no operand"));

//        thread exec([requested, cmd, &executor, &response]() mutable {
            auto pair = executor.Command(requested, cmd);
            response.Send(pair.first, pair.second);
//        });
//        exec.detach();
    } catch (UndefinedCommand) {
        response.Send(StatusCodes::UNKNOWN, "Unknown command");
    } catch (NoDataConnection) {
        response.Send(StatusCodes::NO_DATA_CONNECTION, "No data connection opened");
    } catch (NotLogged) {
        response.Send(StatusCodes::NO_ACCESS, "No access to user this command");
    } catch (AlreadyDeclared) {
        response.Send(StatusCodes::UNKNOWN, "User already logged");
    } catch (logic_error error) {
        response.Send(StatusCodes::UNKNOWN, error.what());
    } catch(const runtime_error& e) {
        logger(Logger::Levels::INFO, "Lost connection");
        return;
    } catch (...) {
        response.Send(StatusCodes::UNKNOWN, "Undefined behavior");
    }
}

void FTPServer::SendBinary(char* buffer, int size) {
    FTPClient request = AcceptMessage(dataFD, false);

    auto logger = Logger::SetPrefix("Datachannel");

    logger(Logger::Levels::INFO, "connection with " + request.GetClientAddress() + ":" + request.GetClientPort());

    write(request.GetClientDescriptor(), (void*)buffer, size);

    logger(Logger::Levels::INFO, "message sent");
    close(request.GetClientDescriptor());
}

void FTPServer::CloseDataServer() {
    dataPort = 0;
    dataChannelInitialized = false;
    close(dataFD);

    auto logger = Logger::SetPrefix("Datachannel");
    logger(Logger::Levels::INFO, "listener destroyed");
}

void FTPServer::ReceiveBinary(char *dest, int size) {
    FTPClient request = AcceptMessage(dataFD, false);
    auto logger = Logger::SetPrefix("Datachannel");

    logger(Logger::Levels::INFO, "receive user binary");

    int bytesRead = 0;
    int result = 1;
    while ((result = read(request.GetClientDescriptor(), dest + bytesRead, size - bytesRead)) != 0)
    {
        bytesRead += result;
    }

    close(request.GetClientDescriptor());

    logger(Logger::Levels::INFO, "receive user binary completed");
}

bool FTPServer::SetNonBlocking(int descriptor, bool blocking) {
    if (descriptor < 0) return false;

    int flags = fcntl(descriptor, F_GETFL, 0);
    if (flags == -1) return false;
    flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    return fcntl(descriptor, F_SETFL, flags) == 0;
}
