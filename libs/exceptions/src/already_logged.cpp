#include <already_logged.h>

std::string AlreadyLogged::resolve() const noexcept {
    return "Client already logged";
}

const char *AlreadyLogged::what() const noexcept {
    return "Client already logged";
}

