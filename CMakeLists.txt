
cmake_minimum_required(VERSION 3.10)

enable_language(CXX)
include(GNUInstallDirs)
include(cmake/main.cmake)

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.224.tar.gz"
        SHA1 "18e57a43efc435f2e1dae1291e82e42afbf940be"
)

get_project_name("${CMAKE_CURRENT_SOURCE_DIR}" "PROJECT_NAME")
project(${PROJECT_NAME}
        VERSION 0.1.1
        DESCRIPTION "Simple project")

initialize_project(${CMAKE_CURRENT_SOURCE_DIR})

#FIND_PACKAGE(Threads REQUIRED)
#TARGET_LINK_LIBRARIES(FTPServer Threads::Threads)
#TARGET_COMPILE_OPTIONS(FTPServer INTERFACE Threads::Threads)
#
#target_link_libraries(FTPServer stdc++fs)