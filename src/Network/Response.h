#pragma once

#include <map>
#include <string>
#include <initializer_list>

#include "Client.h"
#include "StatusCodes.h"

using namespace std;

class FTPResponse {
private:
    FTPClient request;
    string message;
public:
    FTPResponse(FTPClient req) : request(req) {};
    string Prepare(StatusCodes code, initializer_list<string> params, char *dest);
    void ReadMessage(string message);
    void Send();
};