cmake_minimum_required(VERSION 3.16)
project(lwlog CXX)

option(LWLOG_BUILD_EXAMPLES "Build example program" ON)

find_package(Threads REQUIRED)

add_library(lwlog
    src/registry.cpp
    src/lwlog.cpp
    src/policy/log_policy.cpp
    src/details/pattern/alignment_formatter.cpp
    src/details/pattern/pattern.cpp
    src/details/file_writer.cpp)
add_library(lwlog::lwlog ALIAS lwlog)
target_include_directories(lwlog PUBLIC src)
target_link_libraries(lwlog PUBLIC Threads::Threads)
target_compile_features(lwlog PUBLIC cxx_std_17)

add_subdirectory(examples)
