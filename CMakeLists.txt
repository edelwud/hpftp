cmake_minimum_required(VERSION 3.10)

# set the project name
project(FTPServer C CXX)

# add the executable
add_executable(FTPServer main.cpp Server.h Server.cpp)

# including pthread.h library
SET(THREADS_PREFER_PTHREAD_FLAG TRUE)
FIND_PACKAGE(Threads REQUIRED)
TARGET_LINK_LIBRARIES(FTPServer Threads::Threads)
TARGET_COMPILE_OPTIONS(FTPServer INTERFACE Threads::Threads)