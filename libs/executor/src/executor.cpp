#include <executor.h>

#include <exceptions/no_data_connection.h>
#include <fstream>

pair<StatusCodes, string> Executor::Command(CommandList code, string argument) {
    switch (code) {
        case CommandList::CWD: {
            if (argument.empty()) this->CWD("/");
            else this->CWD(argument);
            return { StatusCodes::DIRECTORY_CHANGED, "Current path: " + this->currentPath };
        }
        case CommandList::ABOR:
            break;
        case CommandList::CDUP:
            break;
        case CommandList::DELE: {
            string base = this->currentPath + '/' + argument;
            this->exec("rm -R \"" + base + "\"");
            return { StatusCodes::DIRECTORY_CHANGED, "Ok." };
        }
        case CommandList::EPSV:
            FTPServer::InitDataServer();
            return { StatusCodes::EXTENDING_PASSIVE, "Entering Extended Passive Mode (|||" + to_string(FTPServer::dataPort) + "|)." };
        case CommandList::HELP:
            break;
        case CommandList::LIST:
            this->LIST();
            return { StatusCodes::DIRECTORY_SEND, "Directory send OK." };

        case CommandList::MDTM:
            break;
        case CommandList::MKD: {
            string base = this->currentPath + '/' + argument;
            this->exec("mkdir \"" + base + "\"");
            return { StatusCodes::DIR_MADE, "Directory created" };
        }
        case CommandList::NLST:
            break;
        case CommandList::NOOP:
            break;
        case CommandList::PASS:
            if (argument.empty()) break;
            this->PASS(argument);
            if (this->client.IsAuthorized()) {
                return { StatusCodes::LOGIN_SUCCESSFUL, "Login successful" };
            }
            return { StatusCodes::SPECIFY_PASSWORD, "Please, specify the password" };

        case CommandList::PASV:
            this->PASV();
            if (!FTPServer::dataChannelInitialized) {
                throw NoDataConnection();
            }
            return { StatusCodes::ENTERING_PASSIVE, "Entering Passive Mode (127,0,0,1," + to_string(FTPServer::dataPort / 256) + "," + to_string(FTPServer::dataPort % 256) + ")." };

        case CommandList::PORT:
            break;
        case CommandList::PWD:
            return { StatusCodes::CURRENT_PATH, "\""+this->currentPath+"\"" };
        case CommandList::QUIT:
            break;
        case CommandList::REIN:
            break;
        case CommandList::RETR:
            if (argument.empty()) {
                return { StatusCodes::UNKNOWN, "Please, specify filename." };
            }
            this->RETR(argument);
            break;
        case CommandList::RMD: {
            string base = this->currentPath + '/' + argument;
            this->exec("rm -R \"" + base + "\"");
            break;
        }
        case CommandList::RNFR: {
            this->renameFrom = this->currentPath + '/' + argument;
            return { StatusCodes::RENAME_FROM, "Renaming accepted" };
        }
        case CommandList::SIZE:
            break;
        case CommandList::STOR: {
            if (!FTPServer::dataChannelInitialized) {
                throw NoDataConnection();
            }
            string base = this->currentPath + "/" + argument;
            this->exec("touch \"" + base + "\"");
            fstream file(base);

            string message = to_string((int)StatusCodes::OPENED_CHANNEL) + " Ok.\n";
            write(this->client.GetClientDescriptor(), (void *)message.data(), message.size());

            char buffer[MAX_BINARY_SIZE];
            FTPServer::ReceiveBinary(buffer);
            FTPServer::CloseDataServer();

            file << buffer;
            file.close();

            return { StatusCodes::FILE_RECEIVE, "File receive OK." };
        }
        case CommandList::SYST:
            break;
        case CommandList::TYPE:
            break;
        case CommandList::USER:
            this->USER(argument);
            if (this->client.IsAuthorized()) {
                return { StatusCodes::LOGIN_SUCCESSFUL, "Login successful" };
            }
            return { StatusCodes::SPECIFY_PASSWORD, "Please, specify the password" };
        case CommandList::RNTO: {
            string base = this->currentPath + '/' + argument;
            this->exec("mv \"" + this->renameFrom + "\" \"" + base + "\"");
        }
    }

    return { StatusCodes::SERVICE_READY, "Ok." };
}

void Executor::CWD(string path) {
    this->currentPath = path;
}

void Executor::LIST() {
    if (!FTPServer::dataChannelInitialized) {
        throw NoDataConnection();
    }

    string result = this->exec("ls \"" + this->currentPath + "\" -all");

    FTPServer::SendBinary(result);
    FTPServer::CloseDataServer();
}

void Executor::USER(string username) {
    if (this->client.IsAuthorized()) {
        throw AlreadyLogged();
    }

    this->client.SetUsername(username);
}

void Executor::PASS(string password) {
    if (this->client.IsAuthorized()) {
        throw AlreadyLogged();
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