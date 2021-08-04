cmake_minimum_required(VERSION 3.10)

include(cmake/main.cmake)

get_project_name("${CMAKE_CURRENT_SOURCE_DIR}" "PROJECT_NAME")
project(${PROJECT_NAME}
        VERSION 0.1.1
        DESCRIPTION "High performance FTP server")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

include(GNUInstallDirs)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")
set(CMAKE_CXX_STANDARD 17)

initialize_project(${CMAKE_CURRENT_SOURCE_DIR})

