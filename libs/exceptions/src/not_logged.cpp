#include <not_logged.h>

std::string NotLogged::resolve() const noexcept {
    return "User not logged";
}

const char *NotLogged::what() const noexcept {
    return "User not logged";
}

