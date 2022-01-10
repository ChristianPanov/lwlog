cmake_minimum_required(VERSION 3.16)
project(lwlog CXX)

option(LWLOG_BUILD_EXAMPLES "Build example program" ON)
option(ENABLE_TESTING ON "Enable tests (implicitly builds examples)")

include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

find_package(Threads REQUIRED)

add_subdirectory(lwlog)

if (ENABLE_TESTING)
  enable_testing()
endif ()

if(LWLOG_BUILD_EXAMPLES OR ENABLE_TESTING)
  add_subdirectory(examples)
endif()
