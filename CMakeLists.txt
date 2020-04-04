cmake_minimum_required(VERSION 3.10)

# set the project name
project(FTPServer C CXX)

# add the executable
add_executable(
    FTPServer src/main.cpp
    
    src/Network/Server.h 
    src/Network/Server.cpp
    
    src/Network/Response.cpp 
    src/Network/Response.h 
    
    src/Network/Request.cpp 
    src/Network/Request.h
    
    src/Command/Command.h

    src/Logger.h
    src/Logger.cpp
)

set_property(TARGET FTPServer PROPERTY CXX_STANDARD 20)

# including pthread.h library
SET(THREADS_PREFER_PTHREAD_FLAG TRUE)
FIND_PACKAGE(Threads REQUIRED)
TARGET_LINK_LIBRARIES(FTPServer Threads::Threads)
TARGET_COMPILE_OPTIONS(FTPServer INTERFACE Threads::Threads)