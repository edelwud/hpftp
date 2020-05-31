#include "Executor.h"

pair<StatusCodes, string> Executor::Command(FTPCommandList code, string argument) {
    switch (code) {
    case FTPCommandList::CWD: {
        if (argument.empty()) this->CWD("/");
        else this->CWD(argument);
        return { StatusCodes::DIRECTORY_CHANGED, "Current path: " + this->client.currentPath };
    }
    case FTPCommandList::ABOR:
        FTPServer::CloseDataServer();
        break;

    case FTPCommandList::CDUP: {
        fs::path path = this->client.currentPath;
        cout << "DEBUG" << path.parent_path() << endl;
        this->CWD(path.parent_path());
        return { StatusCodes::DIRECTORY_CHANGED, "Current path: " + this->client.currentPath };
    }

    case FTPCommandList::DELE: {
        string base = this->client.currentPath + '/' + argument;
        if (!this->exists(base)) {
            throw UndefinedCommand();
        }
        this->exec("rm -f \"" + base + "\"");
        return { StatusCodes::DIRECTORY_CHANGED, "Ok." };
    }
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
    case FTPCommandList::MKD: {
        string base = this->client.currentPath + '/' + argument;
        if (this->exists(base)) {
            throw UndefinedCommand();
        }
        this->exec("mkdir \"" + base + "\"");
        return { StatusCodes::DIR_MADE, "Directory created" };
    }
    case FTPCommandList::NLST:
        break;
    case FTPCommandList::NOOP:
        break;
    case FTPCommandList::PASS:
        if (argument.empty()) break;
        this->PASS(argument);
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
        return { StatusCodes::CURRENT_PATH, "\""+this->client.currentPath+"\"" };
    case FTPCommandList::QUIT:
        break;
    case FTPCommandList::REIN:
        break;
    case FTPCommandList::RETR:
        if (argument.empty()) {
            return { StatusCodes::UNKNOWN, "Please, specify filename." };
        }
        this->RETR(argument);
        break;
    case FTPCommandList::RMD: {
        string base = this->client.currentPath + '/' + argument;
        this->exec("rm -rf \"" + base + "\"");
        break;
    }
    case FTPCommandList::RNFR: {
        this->renameFrom = this->client.currentPath + '/' + argument;
        return { StatusCodes::RENAME_FROM, "Renaming accepted" };
    }
    case FTPCommandList::SIZE:
        break;
    case FTPCommandList::STOR: {
        if (!FTPServer::dataChannelInitialized) {
            throw NoDataConnection();
        }
        string base = this->client.currentPath + "/" + argument;
        this->exec("touch \"" + base + "\"");
        fstream file;
        this->binary ? file.open(base, ios::binary) : file.open(base);

        string message = to_string((int)StatusCodes::OPENED_CHANNEL) + " Ok.\n";
        write(this->client.GetClientDescriptor(), (void *)message.data(), message.size());

        char *buffer = new char[MAX_BINARY_SIZE];
        FTPServer::ReceiveBinary(buffer, MAX_BINARY_SIZE);
        FTPServer::CloseDataServer();

        file << buffer;
        file.close();

        return { StatusCodes::FILE_RECEIVE, "File receive OK." };
    }
    case FTPCommandList::SYST:
        break;
    case FTPCommandList::TYPE:
        this->binary = argument == "I";
        break;
    case FTPCommandList::USER:
        this->USER(argument);
        if (this->client.IsAuthorized()) {
            return { StatusCodes::LOGIN_SUCCESSFUL, "Login successful" };
        }
        return { StatusCodes::SPECIFY_PASSWORD, "Please, specify the password" };
    case FTPCommandList::RNTO: {
        string base = this->client.currentPath + '/' + argument;
        this->exec("mv \"" + this->renameFrom + "\" \"" + base + "\"");
    }
    }

    return { StatusCodes::SERVICE_READY, "Ok." };
}

void Executor::CWD(string path) {
    auto iter = find(path.begin(), path.end(), '/');

    string prevPath = this->client.currentPath;
    iter != path.end() ?
        this->client.currentPath = path :
        this->client.currentPath += '/' + path;
    if (!this->exists(this->client.currentPath)) {
        Logger::Print(Logger::Levels::ERROR, path);
        this->client.currentPath = prevPath;
        throw UndefinedCommand();
    }
}

void Executor::LIST() {
    if (!FTPServer::dataChannelInitialized) {
        throw NoDataConnection();
    }

    string result = this->exec("ls \"" + this->client.currentPath + "\" -all");

    FTPServer::SendBinary(const_cast<char *>(result.data()), result.size());
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

    fstream fs;
    this->binary ?
        fs.open(this->client.currentPath + "/" + filename, ios::binary) :
        fs.open(this->client.currentPath + "/" + filename);

    int size = fs.rdbuf()->in_avail();
    char *buffer = new char[size];
    fs.read(buffer, size);

    FTPServer::SendBinary(buffer, size);
    FTPServer::CloseDataServer();

    delete[] buffer;
}