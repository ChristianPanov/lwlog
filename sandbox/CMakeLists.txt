cmake_minimum_required(VERSION 3.14)

project(lwlog_sandbox CXX)

# ---- Declare dependencies ----

include(FetchContent)
FetchContent_Declare(lwlog SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")

# ---- Import dependencies ----

FetchContent_MakeAvailable(lwlog)

# ---- Declare library ----

add_executable(lwlog_sandbox benchmark.h sandbox.cpp)

target_include_directories(lwlog_sandbox PRIVATE "${PROJECT_SOURCE_DIR}")
target_compile_features(lwlog_sandbox PRIVATE cxx_std_17)
target_link_libraries(lwlog_sandbox PRIVATE lwlog::lwlog)
