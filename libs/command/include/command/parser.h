#pragma once

#include <vector>

#include <command/command.h>

class Parser {
public:
    explicit Parser(const std::string& message);

public:
    Command LoadCommand();

public:
    void SetMessage(const std::string& msg);

public:
    CommandList GetCommandCode();
    std::vector<std::string> GetArgs();

private:

private:
    std::string message;
};