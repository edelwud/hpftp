#include <bind_exception.h>

std::string BindException::resolve() const noexcept {
    return "Cannot listen on port";
}

const char *BindException::what() const noexcept {
    return "Cannot listen on port";
}
