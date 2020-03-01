#include <iostream>

#include "Server.h"

using namespace std;

int main() {
    ServerOptions options = { 4, 8021 };
    FTPServer *server = new FTPServer();
    server->InitServer(options);

    return 0;
}