cmake_minimum_required(VERSION 3.16)
project(lwlog CXX)

option(LWLOG_BUILD_EXAMPLES "Build example program" ON)

include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

find_package(Threads REQUIRED)

add_subdirectory(lwlog)

add_subdirectory(examples)
