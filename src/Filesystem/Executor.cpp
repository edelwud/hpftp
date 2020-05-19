#include "Executor.h"

pair<StatusCodes, string> Executor::Command(FTPCommandList code, vector<string> arguments) {



    return { StatusCodes::SERVICE_READY, this->currentPath };
}