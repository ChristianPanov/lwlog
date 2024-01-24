cmake_minimum_required(VERSION 3.20)

project(LWLOG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_GENERATOR_PLATFORM x64)
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_definitions(__cpp_lib_hardware_interference_size)
endif()

message("Adding source files")
file(GLOB_RECURSE LWLOG_SOURCE_FILES ${CMAKE_SOURCE_DIR}/lwlog/src/*.cpp)
file(GLOB_RECURSE LWLOG_HEADER_FILES ${CMAKE_SOURCE_DIR}/lwlog/src/*.h)

file(GLOB_RECURSE LWLOG_SANDBOX_SOURCE_FILES ${CMAKE_SOURCE_DIR}/Sandbox/*.cpp)
file(GLOB_RECURSE LWLOG_SANDBOX_HEADER_FILES ${CMAKE_SOURCE_DIR}/Sandbox/*.h)

set(LWLOG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lwlog/src/)

message("Creating lwlog lib")
add_library(lwlog_lib STATIC ${LWLOG_SOURCE_FILES} ${LWLOG_HEADER_FILES})

add_executable(lwlog_sandbox ${LWLOG_SANDBOX_SOURCE_FILES} ${LWLOG_SANDBOX_HEADER_FILES})

target_include_directories(lwlog_sandbox PRIVATE ${LWLOG_INCLUDE_DIR})
target_include_directories(lwlog_lib PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/src/)

message("Linking libraries")

target_link_libraries(lwlog_sandbox PRIVATE lwlog_lib)