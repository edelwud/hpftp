#include "DataChannel.h"

void DataChannel::Initialize() {
    if (this->initialized) {
        return;
    }
    this->GeneratePort();
    this->descriptor = FTPServer::CreateSocket(this->port, 10);
    this->initialized = true;
}

int DataChannel::GeneratePort() {
    srand(time(0));
    return this->port = rand() % (65536 - 40000) + 40000;
}

string DataChannel::Status() {
//    DataChannelStatus status;
//    status.Set(IP_ADDRESS, this->port);
    return "";
}

void DataChannel::Accept() {
    sockaddr_in clientAddress{};
    socklen_t addrlen = sizeof(clientAddress);
    int acceptedMessageDesc = accept(this->descriptor, (sockaddr *)&clientAddress, &addrlen);
    if (acceptedMessageDesc < 0) {
        throw logic_error("Accepted message: failed");
    }
}
