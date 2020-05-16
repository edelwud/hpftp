#include "Client.h"

/**
 * Reading and parsing client command
 */ 
FTPClient::Contract FTPClient::Read() {
    char buffer[MAX_BUFFER_SIZE] = { 0 };

    int status = read(this->socketDesc, buffer, MAX_BUFFER_SIZE);
    if (status == -1) {
        throw runtime_error("Can not read from socket descriptor");
    }
    if (status == 0) {
        throw runtime_error("Connection closed");
    }
    return FTPCommand::Unpack(buffer);
}

/**
 * Getting client ip address
 * @return address string
 */
string FTPClient::GetClientAddress() {
    char address[INET_ADDRSTRLEN]{ 0 };
    if (inet_ntop(AF_INET, &this->client.sin_addr.s_addr, address, sizeof(address)) == nullptr) {
        throw runtime_error("Address format is unsupported");
    }
    return address;
}

/**
 * Getting client port
 * @return port string
 */
string FTPClient::GetClientPort() {
    return to_string(this->client.sin_port);
}

/**
 * Getting client descriptor
 * @return descriptor
 */
int FTPClient::GetClientDescriptor() {
    return this->socketDesc;
}