#include <iostream>

#include "./Network/Server.h"

using namespace std;

int main() {
    ServerOptions options = { 4, 8051 };
    FTPServer *server = new FTPServer();
    server->InitServer(options);

    return 0;
}