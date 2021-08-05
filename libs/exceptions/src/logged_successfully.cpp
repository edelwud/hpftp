#include <logged_successfully.h>

std::string LoggedSuccessfully::resolve() const noexcept {
    return "Client log in successfully";
}

const char *LoggedSuccessfully::what() const noexcept {
    return "Client log in successfully";
}
