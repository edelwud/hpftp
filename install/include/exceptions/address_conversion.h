#pragma once

#include <string>

#include <exceptions/internal_exception.h>

class AddressConversion : public InternalException {
    const char *what() const noexcept override;
};
