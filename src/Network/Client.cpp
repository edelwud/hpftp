#include "Client.h"

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
string FTPClient::IsAuthorized() const {
    return this->username;
}

/**
 * User authorization
 * @param username
 * @param password
 */
bool FTPClient::Authorize(string username, string password) {
    if (!this->IsAuthorized().empty()) {
        throw logic_error("Already authorized");
    }

    if (username == ANONYMOUS) {
        this->SetAuthorized(ANONYMOUS);
        return true;
    }

    auto user = find(this->users.begin(), this->users.end(), make_pair(username, password));
    if (user == this->users.end()) {
        throw logic_error("User not found");
    }

    this->SetAuthorized((*user).first);
    return true;
}

/**
 * Setter for user authorization flag
 */
void FTPClient::SetAuthorized(string username) {
    this->username = username;
}
