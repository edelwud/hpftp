#include "Client.h"

#include <iostream>
#include <iconv.h>

/**
 * Reading and parsing client command
 */ 
FTPClient::Contract FTPClient::Read() const {
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
string FTPClient::GetClientPort() const {
    return to_string(this->client.sin_port);
}

/**
 * Getting client descriptor
 * @return descriptor
 */
int FTPClient::GetClientDescriptor() const {
    return this->socketDesc;
}

/**
 * Check current user
 * @return boolean
 */
bool FTPClient::IsAuthorized() const {
    return this->authorized;
}

/**
 * User authorization
 * @param username
 * @param password
 */
void FTPClient::Authorize() {
    if (this->authorized) {
        throw AlreadyDeclared();
    }

    if (this->username == ANONYMOUS) {
        this->authorized = true;
        return;
    }

    auto user = users.find(this->username);
    if (user == this->users.end()) {
        throw logic_error("User not found");
    }

    auto [username, password] = *user;

    if (this->password != password) {
        throw logic_error("User not found");
    }

    this->authorized = true;
    return;
}


void FTPClient::SetUsername(string username) {
    this->username = username;
    if (this->username == ANONYMOUS) {
        this->authorized = true;
        return;
    }
    if (!this->password.empty()) {
        this->Authorize();
    }
}

void FTPClient::SetPassword(string password) {
    this->password = password;
    if (!this->username.empty()) {
        this->Authorize();
    }
}
