#include <undefined_command.h>

const char *UndefinedCommand::what() const noexcept {
    return "Pressed undefined command";
}

std::string UndefinedCommand::resolve() const noexcept {
    return "Pressed undefined command";
}
