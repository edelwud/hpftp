#pragma once

#include <string>
#include <sstream>
#include <regex>
#include <ctime>
#include <iostream>

#include <client/response.h>

#include <server.h>

using namespace std;

class DataChannel {
    bool initialized = false;
    bool connected = false;

    int port = 0;
    int descriptor = 0;
public:
    string Status();
    void Accept();

    void Initialize();
    int GeneratePort();
};
