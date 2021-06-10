#include <command.h>

#include <utility>

#include <command/operations.h>
#include <magic_enum.hpp>
#include <exceptions/undefined_command.h>

Command::Command(CommandList code) : code(code) {}

Command::Command(const std::string& codeName) {
    SetName(codeName);
}

Command::Command(const std::string &codeName, const std::vector<std::string>& args) {
    SetName(codeName);
    SetArgs(args);
}

Command::Command(CommandList codeName, const std::vector<std::string> &args) {
    code = codeName;
    SetArgs(args);
}

CommandList Command::Get() const {
    return code;
}

void Command::Set(CommandList command) {
    code = command;
}

void Command::SetName(const std::string& name) {
    auto command = magic_enum::enum_cast<CommandList>(name);
    if (!command.has_value()) {
        throw UndefinedCommand();
    }
    code = command.value();
}

std::string Command::GetName() const {
    return std::string(magic_enum::enum_name(code));
}

std::string Command::CombineCommand() const {
    return GetName() + " " + Operations::join(args, ARGS_DELIMITER);
}

const std::vector<std::string> &Command::GetArgs() const {
    return args;
}

void Command::SetArgs(std::vector<std::string> arguments) {
    args = std::move(arguments);
}

bool Command::operator==(const Command& command) const {
    if (Get() == command.Get() && GetArgs() == command.GetArgs()) {
        return true;
    }
    return false;
}

bool Command::operator!=(const Command& command) const {
    return !(*this == command);
}
