#pragma once

#include <string>

#include <exceptions/internal_exception.h>

class BindException : public InternalException {
    const char * what() const noexcept override;
    std::string resolve() const noexcept override;
};
