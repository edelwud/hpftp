#include "Logger.h"

void Logger::Info(string_view message) {
    stringstream stream;
    stream << "Info: " << message << endl;

    ofstream logFile("./info_log.txt", ios::app);
    logFile << stream.str();
    cout << stream.str();
}

void Logger::Warning(string_view message) {
    stringstream stream;
    stream << "Warning: " << message << endl;

    ofstream logFile("warning_log.txt", ios::app);
    logFile << stream.str();
    cout << stream.str();
}

void Logger::Error(string_view message) {
    stringstream stream;
    stream << "Error: " << message << endl;

    ofstream logFile("error_log.txt", ios::app);
    logFile << stream.str();
    cout << stream.str();
}

Logger::Progress Logger::CreateTask(string title, int numberOfTasks) {
    ofstream logFile("task_log.txt", ios::app);

    return [=](string completedTask) {
        static int currentTask = 0;
        stringstream stream;

        if (numberOfTasks < currentTask)
            return;
        if (currentTask == 0) {
            stream << "Task: " << title << endl; 
        }

        stream << title << " [" << ++currentTask << '/' << numberOfTasks << "]: " << completedTask << endl;

        ofstream logFile("error_log.txt", ios::app);
        logFile << stream.str();
        cout << stream.str();
    };
}