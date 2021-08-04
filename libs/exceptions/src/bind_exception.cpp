#include <bind_exception.h>

const char *BindException::what() const noexcept {
    return "Cannot bind to port";
}
