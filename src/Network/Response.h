#ifndef RESPONSE_H
#define RESPONSE_H

#include <map>
#include <string>
#include <initializer_list>

#include "Request.h"
#include "StatusCodes.h"

using namespace std;

class FTPResponse {
private:
    FTPRequest request;
    string message;
public:
    FTPResponse(FTPRequest req) : request(req) {};
    string Prepare(StatusCodes code, initializer_list<string> params, char *dest);
    void ReadMessage(string message);
    void Send();
};

#endif