#pragma once

#include <string>
#include <sstream>
#include <regex>
#include <ctime>
#include <iostream>

#include "Server.h"
#include "Response.h"

using namespace std;
//
//struct DataChannelStatus {
//    char h1, h2, h3, h4;
//    char p1, p2;
//
//    void Set(string ip, unsigned short port) {
//        regex ipParser("(.+).(.+).(.+).(.+)");
//        smatch match;
//
//        if (!regex_match(ip, match, ipParser)) {
//            throw logic_error("Unable to search read string");
//        }
//
//        if (match.empty()) {
//            throw logic_error("Read command not specificed");
//        }
//
//        this->h1 = stoi(match.str(1));
//        this->h2 = stoi(match.str(2));
//        this->h3 = stoi(match.str(3));
//        this->h4 = stoi(match.str(4));
//
//        this->p1 = port / 256;
//        this->p1 = port % 256;
//    }
//
//    string ToString() const {
//        stringstream stream;
//        stream << '(' << h1 << ',' << h2 << ',' << h3 << ',' << h4;
//        stream << p1 << ',' << p2 << ')';
//        return stream.str();
//    }
//};

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
