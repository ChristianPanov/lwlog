cmake_minimum_required(VERSION 3.16)

project(lwlog)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")
message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

set(version 1.2.0)

message("Adding source files")
set(LWLOG_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/lwlog/src/registry.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/alignment_formatter.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/attribute.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/src/details/pattern/pattern.cpp
)

message("Creating lwlog library")
add_library(lwlog_lib ${LWLOG_SOURCE_FILES})
target_include_directories(lwlog_lib PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/src/)
add_library(lwlog::lwlog_lib ALIAS lwlog_lib)

message("Creating lwlog sandbox")
add_executable(lwlog_sandbox ${CMAKE_SOURCE_DIR}/Sandbox/Sandbox.cpp)
target_include_directories(lwlog_sandbox PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/src/)

message("Linking libraries")
target_link_libraries(lwlog_lib PRIVATE Threads::Threads)
target_link_libraries(lwlog_sandbox PRIVATE lwlog_lib)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/lwlog/src
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  FILES_MATCHING PATTERN "*.h"
)

install(TARGETS lwlog_lib
  EXPORT lwlog_libTargets
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT lwlog_libTargets
  FILE lwlog_lib-targets.cmake
  NAMESPACE lwlog::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-configVersion.cmake"
  VERSION ${version}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
 ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
 "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-config.cmake"
 INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-configVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake
)

export(EXPORT lwlog_libTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/lwlog_lib-targets.cmake"
  NAMESPACE lwlog::
)