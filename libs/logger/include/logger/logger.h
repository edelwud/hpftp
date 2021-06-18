#pragma once

#include <string>
#include <functional>

#include <logger/levels.h>

class Logger {
public:
    Logger() = default;

    explicit Logger(Levels level);
    Logger(Levels level, std::string prefix);
    Logger(Levels level, std::string prefix, int tasksNumber);

    explicit Logger(std::string prefix);
    Logger(std::string prefix, int tasksNumber);

public:
    void Print(const std::string& message);

    Logger CreateTask(const std::string& title, int numberOfTasks);
    void ResolveTask();

public:
    [[nodiscard]] Levels getLevel() const;
    void setLevel(Levels level);

    [[nodiscard]] const std::string& getPrefix() const;
    void setPrefix(std::string prefix);

    void setShowTimestamp(bool show);

private:
    static std::string getTimestamp();
    std::string formatMessage(const std::string& message);

private:
    bool showTimestamp = false;
    int taskSummary = 0;
    int currentTask = 0;
    Levels currentLevel = Levels::INFO;
    std::string currentPrefix;
    std::string taskPrefix;
};