#pragma once

#include <stdexcept>

class InternalException : public std::exception {
public:
    virtual std::string resolve() const noexcept = 0;
};