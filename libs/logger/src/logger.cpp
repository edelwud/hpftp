#include <logger.h>

#include <ctime>
#include <iostream>
#include <sstream>
#include <utility>

#include <magic_enum.hpp>

Logger::Logger(Levels level) : currentLevel(level) {}

Logger::Logger(Levels level, std::string prefix) : Logger(level) {
    currentPrefix = std::move(prefix);
}

Logger::Logger(Levels level, std::string prefix, int tasksNumber) : Logger(level) {
    taskSummary = tasksNumber;
    taskPrefix = std::move(prefix);
}

Logger::Logger(std::string prefix) {
    currentPrefix = std::move(prefix);
}

Logger::Logger(std::string prefix, int tasksNumber) : Logger(std::move(prefix)) {
    taskSummary = tasksNumber;
}

void Logger::Print(const std::string &message) {
    std::cout << formatMessage(message) << std::endl;
}

std::string Logger::getTimestamp() {
    std::time_t result = std::time(nullptr);
    std::string localeString = std::asctime(std::localtime(&result));
    return localeString.substr(0, localeString.size() - 1);
}

Levels Logger::getLevel() const {
    return currentLevel;
}

void Logger::setLevel(Levels level) {
    currentLevel = level;
}

const std::string &Logger::getPrefix() const {
    return currentPrefix;
}

void Logger::setPrefix(std::string prefix) {
    currentPrefix = std::move(prefix);
}

void Logger::setShowTimestamp(bool show) {
    showTimestamp = show;
}

void Logger::ResolveTask() {
    currentTask = 0;
    taskSummary = 0;
}

Logger Logger::CreateTask(const std::string &title, int numberOfTasks) {
    std::cout << "[TASK] " << title << std::endl;
    return Logger(currentLevel, title, numberOfTasks);
}

std::string Logger::formatMessage(const std::string &message) {
    std::stringstream stream;

    taskSummary ? stream << '[' << taskPrefix << ']' : stream << std::string();
    if (taskSummary && ++currentTask == taskSummary) {
        currentTask = 0;
        taskSummary = 0;
    }

    stream << "[" << magic_enum::enum_name(currentLevel);
    showTimestamp ? stream << ' ' << getTimestamp() << ']' : stream << ']';
    !currentPrefix.empty() ? stream << '[' << currentPrefix << ']' : stream << std::string();
    stream << ' ' << message;
    return stream.str();
}
