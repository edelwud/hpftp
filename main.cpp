#include <iostream>

#include "Server.h"

int main() {
    ServerOptions options = { 4 };
    FTPServer *server = new FTPServer();
    server->InitServer(options);
    server->AddRequestHandler(FTPCommandList::LS, [&](FTPServerResponse response) {
        
    });

    return 0;
}