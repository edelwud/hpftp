#include <lost_connection.h>

std::string LostConnection::resolve() const noexcept {
    return "Client lost connection";
}

const char *LostConnection::what() const noexcept {
    return "Client lost connection";
}
