#pragma once

#include <map>
#include <string>
#include <vector>

#include <command/supported.h>

#define ARGS_DELIMITER " "

/**
 * @class
 * FTP command
 * Packing and unpacking messages
 */
class Command {
public:
    explicit Command() = default;
    explicit Command(CommandList code);
    explicit Command(CommandList code, const std::vector<std::string> &args);
    explicit Command(const std::string &codeName);
    explicit Command(const std::string &codeName,
                     const std::vector<std::string> &args);

public:
    bool operator==(const Command &command) const;
    bool operator!=(const Command &command) const;

public:
    [[nodiscard]] std::string GetName() const;
    void SetName(const std::string &name);

    [[nodiscard]] CommandList Get() const;
    void Set(CommandList code);

    [[nodiscard]] const std::vector<std::string> &GetArgs() const;
    void SetArgs(std::vector<std::string> arguments);

public:
    [[nodiscard]] std::string CombineCommand() const;

private:
    CommandList code = CommandList::NOOP;
    std::vector<std::string> args;
};