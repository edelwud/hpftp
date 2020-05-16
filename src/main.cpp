#include <iostream>

#include "./Network/Server.h"

using namespace std;

int main() {
    ServerOptions options = { 4, 50505 };
    FTPServer *server = new FTPServer();
    server->InitServer(options);

    return 0;
}