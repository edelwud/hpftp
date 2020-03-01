cmake_minimum_required(VERSION 3.10)

# set the project name
project(FTPServer)

# add the executable
add_executable(FTPServer main.cpp Server.h Server.cpp)