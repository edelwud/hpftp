#include "Response.h"

/*
 * Sending message to client
 * code - status code
 * message - message to client
 */
void FTPResponse::Send(StatusCodes code, string message) {
    stringstream output;
    output << (int)code << ' ' << message << endl;

    int descriptor = this->request.GetClientDescriptor();
    char *buffer = output.str().data();

    write(descriptor, (void*)buffer, output.str().size());
}

void FTPResponse::InitializeDataChannel() {
    this->dataChannel.Initialize();
}
