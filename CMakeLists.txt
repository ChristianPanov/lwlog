cmake_minimum_required(VERSION 3.16)

project(lwlog)

find_package(Threads REQUIRED)

message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

set(version 1.3.0)

message("Adding source files")
set(LWLOG_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/lwlog/include/details/topic_registry.cpp
    ${CMAKE_SOURCE_DIR}/lwlog/include/details/pattern/attribute.cpp
)

message("Creating lwlog library")
add_library(lwlog_lib STATIC ${LWLOG_SOURCE_FILES})
target_compile_features(lwlog_lib PUBLIC cxx_std_17)
target_include_directories(lwlog_lib PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/include/)
add_library(lwlog::lwlog_lib ALIAS lwlog_lib)

message("Creating lwlog sandbox")
add_executable(lwlog_sandbox ${CMAKE_SOURCE_DIR}/Sandbox/Sandbox.cpp)
target_include_directories(lwlog_sandbox PRIVATE ${CMAKE_SOURCE_DIR}/lwlog/include/)

message("Linking libraries")
target_link_libraries(lwlog_lib PRIVATE Threads::Threads)
target_link_libraries(lwlog_sandbox PRIVATE lwlog_lib)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/lwlog/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lwlog
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