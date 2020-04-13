#include "Logger.h"

void Logger::PrintMessage(string message) {
    stringstream stream;
    stream << message << endl;

    ofstream logFile("./log.txt", ios::app);
    logFile << stream.str();
    cout << stream.str();
    logFile.close();
}

void Logger::Print(Levels level, string message) {
    string result = LevelsMap[level];
    result += ":";
    result += message;
    PrintMessage(result);
}

Logger::Contract Logger::CreateTask(string title, int numberOfTasks) {
    ofstream logFile("task_log.txt", ios::app);
    logFile << "Task: " << title << endl;
    cout << "Task: " << title << endl;
    logFile.close();
    
    return [=](string completedTask) {
        static int currentTask = 0;
        stringstream stream;

        if (numberOfTasks < currentTask)
            return;

        stream << title << " [" << ++currentTask << '/' << numberOfTasks << "]: " << completedTask << endl;

        ofstream logFile("task_log.txt", ios::app);
        logFile << stream.str();
        cout << stream.str();
        logFile.close();
    };
}



function<void(Logger::Levels, string)> Logger::SetPrefix(string prefix) {
    return [=](Logger::Levels level, string message){
        string result = " [" + prefix + "] " + message;
        Logger::Print(level, result);
    };
}
