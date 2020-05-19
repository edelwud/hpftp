#pragma once

#include <map>
#include <string>
#include <sstream>
#include <initializer_list>
#include <utility>

#include <unistd.h>

#include "Client.h"
#include "StatusCodes.h"
#include "DataChannel.h"

using namespace std;

class FTPResponse {
private:
    FTPClient& request;
    DataChannel dataChannel{};
public:
    explicit FTPResponse(FTPClient& req) : request(req) {};

    void InitializeDataChannel();
    string DataChannelStatus();

    void Send(StatusCodes code, string message);
};