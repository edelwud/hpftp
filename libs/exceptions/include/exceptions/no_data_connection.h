#pragma once

#include <string>

#include <exceptions/ftp_exception.h>

class NoDataConnection : public FTPException {
    const char *what() const noexcept override;
    std::string resolve() const noexcept override;
};
