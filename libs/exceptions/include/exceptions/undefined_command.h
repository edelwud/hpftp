#pragma once

#include <string>

#include <exceptions/ftp_exception.h>

class UndefinedCommand : public FTPException {
    const char * what() const noexcept override;
    std::string resolve() const noexcept override;
};