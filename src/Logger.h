#pragma once

#include <string_view>
#include <sstream>
#include <iostream>
#include <fstream>
#include <functional>

using namespace std;

class Logger {
public:
    using Progress = function<void(string)>;
    
    static void Info(string_view message);
    static void Warning(string_view message);
    static void Error(string_view message);

    static Progress CreateTask(string title, int numberOfTasks);
};