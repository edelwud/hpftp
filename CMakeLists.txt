cmake_minimum_required(VERSION 3.10)

include(GNUInstallDirs)
include(cmake/main.cmake)

CPMAddPackage(
        NAME magic_enum
        GITHUB_REPOSITORY Neargye/magic_enum
        GIT_TAG v0.7.2
        OPTIONS "MAGIC_ENUM_OPT_BUILD_EXAMPLES NO;MAGIC_ENUM_OPT_BUILD_TESTS NO"
)

CPMAddPackage(
        NAME GTest
        GITHUB_REPOSITORY google/googletest
        GIT_TAG release-1.11.0
)

CPMAddPackage(
        NAME libuv
        GITHUB_REPOSITORY libuv/libuv
        GIT_TAG v1.41.0
        OPTIONS "LIBUV_BUILD_BENCH NO;LIBUV_BUILD_TESTS NO"
)

CPMAddPackage(
        NAME openssl
        GITHUB_REPOSITORY microcai/openssl-cmake
        GIT_TAG master
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install")
set(CMAKE_CXX_STANDARD 17)

get_project_name("${CMAKE_CURRENT_SOURCE_DIR}" "PROJECT_NAME")
project(${PROJECT_NAME}
        VERSION 0.1.1
        DESCRIPTION "High performance FTP server")

initialize_project(${CMAKE_CURRENT_SOURCE_DIR})

