cmake_minimum_required(VERSION 3.16)

project(lwlog VERSION 1.6.0 LANGUAGES CXX)

find_package(Threads REQUIRED)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

message("Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

message("Adding source files")
set(LWLOG_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/details/topic_registry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/details/os/time_point.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/details/pattern/pattern_instruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/details/pattern/custom_field.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/details/pattern/compiler/parser.cpp
) 

message("Creating lwlog library")
add_library(lwlog_lib STATIC ${LWLOG_SOURCE_FILES})
add_library(lwlog::lwlog_lib ALIAS lwlog_lib)

target_compile_features(lwlog_lib PUBLIC cxx_std_17)

target_include_directories(lwlog_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

message("Creating lwlog sandbox")
add_executable(lwlog_sandbox ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/Sandbox.cpp)

message("Linking libraries")
target_link_libraries(lwlog_lib PRIVATE Threads::Threads)
target_link_libraries(lwlog_sandbox PRIVATE lwlog_lib)

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lwlog/include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lwlog
  FILES_MATCHING PATTERN "*.h"
)

install(TARGETS lwlog_lib
  EXPORT lwlog_libTargets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT lwlog_libTargets
  FILE lwlog_lib-targets.cmake
  NAMESPACE lwlog::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lwlog_lib
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-configVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
 ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
 "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-config.cmake"
 INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lwlog_lib
)

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/lwlog_lib-configVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/lwlog_lib
)

export(EXPORT lwlog_libTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/lwlog_lib-targets.cmake"
  NAMESPACE lwlog::
)