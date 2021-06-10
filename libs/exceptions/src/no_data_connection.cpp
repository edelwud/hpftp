#include <no_data_connection.h>

std::string NoDataConnection::resolve() const noexcept {
    return "No data connection between client and server";
}

const char *NoDataConnection::what() const noexcept {
    return "No data connection between client and server";
}
