#include <server.h>

#include <logger/logger.h>

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
        FTPClient request = FTPServer::AcceptMessage(this->cmdFD);
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

    Logger::Print(Logger::Levels::INFO, "Data channel binded on port " + to_string(dataPort));
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
    if (listen(serverFileDescriptor, connectionsQueue) < 0) {
        throw runtime_error("Listening on socket: failed");
    }
    progress("listening port");

    return serverFileDescriptor;
}

/**
 * Accepting user message from file descriptor
 */
FTPClient FTPServer::AcceptMessage(int listenConnDescriptor) {
    sockaddr_in clientAddress{};
    socklen_t addrlen = sizeof(clientAddress);
    int acceptedMessageDesc = accept(listenConnDescriptor, (sockaddr *)&clientAddress, &addrlen);
    if (acceptedMessageDesc < 0) {
        throw runtime_error("Accepted message: failed");
    }
    return FTPClient{ acceptedMessageDesc, clientAddress };
}

/**
 * Request manager
 * @param request connection descriptor
 */
void FTPServer::ManageRequest(FTPClient &request) {
    auto logger = Logger::SetPrefix(request.GetClientAddress() + ":" + request.GetClientPort());

    struct passwd *pw = getpwuid(getuid());
    string currentDir = pw->pw_dir;

    FTPResponse response(request);
    Executor executor(request, currentDir);

    response.Send(StatusCodes::SERVICE_READY, "Welcome");

    while (true) try {
            auto [requested, cmd] = request.Read();
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

            auto [code, message] = executor.Command(requested, cmd);
            response.Send(code, message);

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

void FTPServer::SendBinary(string message) {
    FTPClient request = AcceptMessage(dataFD);

    Logger::Print(Logger::Levels::INFO, "Somebody with ip " + request.GetClientAddress() + " connected");

    char *buffer = const_cast<char *>(message.data());

    write(request.GetClientDescriptor(), (void*)buffer, message.size());
    close(request.GetClientDescriptor());
}

void FTPServer::CloseDataServer() {
    dataPort = 0;
    dataChannelInitialized = false;
    close(dataFD);
}

void FTPServer::ReceiveBinary(char dest[MAX_BUFFER_SIZE]) {
    FTPClient request = AcceptMessage(dataFD);

    Logger::Print(Logger::Levels::INFO, "Receive user binary.");

    read(request.GetClientDescriptor(), dest, MAX_BINARY_SIZE);
    close(request.GetClientDescriptor());

    Logger::Print(Logger::Levels::INFO, "Receive user binary completed");
}
