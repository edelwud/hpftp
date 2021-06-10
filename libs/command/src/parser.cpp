#include <parser.h>

#include <regex>

#include <magic_enum.hpp>

#include <command/operations.h>
#include <exceptions/undefined_command.h>

Parser::Parser(const std::string& message) {
    SetMessage(message);
}

CommandList Parser::GetCommandCode() {
    std::regex commandParser("([A-Za-z]+) +(.+)");
    std::smatch match;
    if (!regex_match(message, match, commandParser) || match.empty()) {
        throw UndefinedCommand();
    }

    std::string commandString = match.str(1);
    for_each(commandString.begin(), commandString.end(), [](char &element){ element = toupper(element); });

    auto command = magic_enum::enum_cast<CommandList>(commandString);
    if (!command.has_value()) {
        throw UndefinedCommand();
    }

    return command.value();
}

std::vector<std::string> Parser::GetArgs() {
    std::regex commandParser("([A-Za-z]+) +(.+)");
    std::smatch match;
    if (!regex_match(message, match, commandParser) || match.empty()) {
        throw UndefinedCommand();
    }

    std::string argsString = match.str(2);
    return Operations::split(argsString, ARGS_DELIMITER);
}

void Parser::SetMessage(const std::string& msg) {
    message = Operations::trim(msg);
}

Command Parser::LoadCommand() {
    return Command(GetCommandCode(), GetArgs());
}
