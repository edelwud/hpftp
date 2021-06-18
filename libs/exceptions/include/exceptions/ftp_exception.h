#pragma once

#include <stdexcept>

class FTPException : public std::exception {
public:
    virtual std::string resolve() const noexcept = 0;
};