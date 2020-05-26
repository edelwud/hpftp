#include "Response.h"

/*
 * Sending message to client
 * code - status code
 * message - message to client
 */
void FTPResponse::Send(StatusCodes code, string message) {
    stringstream output;
    output << (int)code << ' ' << message << '\n';

    int descriptor = this->request.GetClientDescriptor();
    char *buffer = const_cast<char *>(output.str().data());

    write(descriptor, (void*)buffer, output.str().size());
}

void FTPResponse::SendBinary(string message) {
    FTPClient request = FTPServer::AcceptMessage(FTPServer::dataFD);

    Logger::Print(Logger::Levels::INFO, "Somebody with ip " + request.GetClientAddress() + " connected");

    int descriptor = FTPServer::dataFD;
    char *buffer = const_cast<char *>(message.data());

    write(descriptor, (void*)buffer, message.size());
}
