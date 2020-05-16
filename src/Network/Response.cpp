#include "Response.h"

string FTPResponse::Prepare(StatusCodes code, initializer_list<string> params, char *dest) {
    return "";
}

void FTPResponse::ReadMessage(string message) {
    return;
}

/*
 * Sending message to client
 * code - status code
 * message - message to client
 */
void FTPResponse::Send(StatusCodes code, string message) {
    stringstream output;
    output << (int)code << ' ' << message;

    int descriptor = this->request.GetClientDescriptor();
    char *buffer = output.str().data();

    write(descriptor, (void*)buffer, output.str().size());
}