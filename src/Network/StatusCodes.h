#ifndef STATUS_CODES_H
#define STATUS_CODES_H

using namespace std;

enum class StatusCodes {
    NOT_INIT = 100,
    COMMENT = 110,
    NOT_REALIZED = 120,
    OPENED_CHANNEL = 125,
    SERVICE_READY = 220
};

#endif