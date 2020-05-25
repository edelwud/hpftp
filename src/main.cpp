#include <iostream>

#include "./Network/Server.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru-RU");

    ServerOptions options = { 4, 50505 };
    FTPServer *server = new FTPServer();
    server->InitServer(options);

    return 0;
}