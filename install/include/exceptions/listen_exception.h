#pragma once

#include <string>

#include <exceptions/internal_exception.h>

class ListenException : public InternalException {
    const char *what() const noexcept override;
};
