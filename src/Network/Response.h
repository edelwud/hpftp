#pragma once

#include <map>
#include <string>
#include <sstream>
#include <initializer_list>

#include <unistd.h>

#include "Client.h"
#include "StatusCodes.h"

using namespace std;

class FTPResponse {
private:
    FTPClient request;
    string message;
public:
    explicit FTPResponse(FTPClient req) : request(req) {};
    string Prepare(StatusCodes code, initializer_list<string> params, char *dest);
    void ReadMessage(string message);

    void Send(StatusCodes code, string message);
};