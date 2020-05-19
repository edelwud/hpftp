#pragma once

using namespace std;

enum class StatusCodes {
    NOT_INIT = 100,
    COMMENT = 110,
    NOT_REALIZED = 120,
    OPENED_CHANNEL = 125,
    SERVICE_READY = 220,
    UNKNOWN = 500
};