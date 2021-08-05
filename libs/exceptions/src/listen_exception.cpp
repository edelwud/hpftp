#include <listen_exception.h>

const char *ListenException::what() const noexcept {
    return "Cannot listen on port";
}
