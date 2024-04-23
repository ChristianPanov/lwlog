cmake_minimum_required(VERSION 3.16)

project(lwlog)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

message("Adding source files")
set(LWLOG_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/lwlog/src/registry.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/alignment_formatter.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/attribute.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/pattern.cpp
)

message("Creating lwlog library")
add_library(lwlog_lib STATIC ${LWLOG_SOURCE_FILES})
target_include_directories(lwlog_lib PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/src/)

message("Creating lwlog sandbox")
add_executable(lwlog_sandbox ${CMAKE_SOURCE_DIR}/Sandbox/Sandbox.cpp)
target_include_directories(lwlog_sandbox PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/src/)

message("Linking libraries")
target_link_libraries(lwlog_lib PRIVATE Threads::Threads)
target_link_libraries(lwlog_sandbox PRIVATE lwlog_lib)