#include "Executor.h"

pair<StatusCodes, string> Executor::Command(FTPCommandList code, vector<string> arguments) {
    switch (code) {
    case FTPCommandList::CWD: {
        if (arguments.empty()) this->CWD("/");
        else this->CWD(arguments[0]);
        string currPath = fs::current_path();
        return { StatusCodes::DIRECTORY_CHANGED, "Current path: " + currPath };
    }
    case FTPCommandList::ABOR:
        break;
    case FTPCommandList::CDUP:
        break;
    case FTPCommandList::DELE:
        break;
    case FTPCommandList::EPSV:
        FTPServer::InitDataServer();
        return { StatusCodes::EXTENDING_PASSIVE, "Entering Extended Passive Mode (|||" + to_string(FTPServer::dataPort) + "|)." };
    case FTPCommandList::HELP:
        break;
    case FTPCommandList::LIST:
        this->LIST();
        return { StatusCodes::DIRECTORY_SEND, "Directory send OK." };

    case FTPCommandList::MDTM:
        break;
    case FTPCommandList::MKD:
        break;
    case FTPCommandList::NLST:
        break;
    case FTPCommandList::NOOP:
        break;
    case FTPCommandList::PASS:
        this->PASS(arguments[0]);
        if (this->client.IsAuthorized()) {
            return { StatusCodes::LOGIN_SUCCESSFUL, "Login successful" };
        }
        return { StatusCodes::SPECIFY_PASSWORD, "Please, specify the password" };

    case FTPCommandList::PASV:
        this->PASV();
        if (!FTPServer::dataChannelInitialized) {
            throw NoDataConnection();
        }
        return { StatusCodes::ENTERING_PASSIVE, "Entering Passive Mode (127,0,0,1," + to_string(FTPServer::dataPort / 256) + "," + to_string(FTPServer::dataPort % 256) + ")." };

    case FTPCommandList::PORT:
        break;
    case FTPCommandList::PWD:
        return { StatusCodes::CURRENT_PATH, "\""+this->currentPath+"\"" };
    case FTPCommandList::QUIT:
        break;
    case FTPCommandList::REIN:
        break;
    case FTPCommandList::RETR:
        if (arguments[0].empty()) {
            return { StatusCodes::UNKNOWN, "Please, specify filename." };
        }
        this->RETR(arguments[0]);
        break;
    case FTPCommandList::RMD:
        break;
    case FTPCommandList::RNFR:
        break;
    case FTPCommandList::SIZE:
        break;
    case FTPCommandList::STOR:
        break;
    case FTPCommandList::SYST:
        break;
    case FTPCommandList::TYPE:
        break;
    case FTPCommandList::USER:
        this->USER(arguments[0]);
        if (this->client.IsAuthorized()) {
            return { StatusCodes::LOGIN_SUCCESSFUL, "Login successful" };
        }
        return { StatusCodes::SPECIFY_PASSWORD, "Please, specify the password" };
    }

    return { StatusCodes::SERVICE_READY, "Ok." };
}

void Executor::CWD(string path) {
    string temp = this->currentPath;
    this->currentPath = path;
    try {
        fs::current_path(this->currentPath);
    } catch (...) {
        this->currentPath = temp;
    }
}

void Executor::LIST() {
    if (!FTPServer::dataChannelInitialized) {
        throw NoDataConnection();
    }

    string result = this->exec("ls -all");

    FTPServer::SendBinary(result);
    FTPServer::CloseDataServer();
}

void Executor::USER(string username) {
    if (this->client.IsAuthorized()) {
        throw AlreadyDeclared();
    }

    this->client.SetUsername(username);
}

void Executor::PASS(string password) {
    if (this->client.IsAuthorized()) {
        throw AlreadyDeclared();
    }

    this->client.SetPassword(password);
}

void Executor::PASV() {
    FTPServer::InitDataServer();
}

void Executor::RETR(string filename) {
    if (!FTPServer::dataChannelInitialized) {
        throw NoDataConnection();
    }

    fstream fs(this->currentPath + "/" + filename);
    int size = fs.rdbuf()->in_avail();
    char *buffer = new char[size];
    fs.read(buffer, size);

    FTPServer::SendBinary(buffer);
    FTPServer::CloseDataServer();

    delete[] buffer;
}