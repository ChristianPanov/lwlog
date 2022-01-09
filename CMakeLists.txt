cmake_minimum_required(VERSION 3.16)
project(lwlog
  LANGUAGES CXX
  DESCRIPTION "Light Weight Logging Library"
  HOMEPAGE_URL "https://github.com/ChristianPanov/lwlog"
  VERSION 1.0.0)

option(LWLOG_BUILD_EXAMPLES "Build example program" ON)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake)

find_package(Threads REQUIRED)

add_subdirectory(lwlog)

configure_package_config_file(cmake/lwlog-config.cmake.in
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/lwlog/lwlog-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/lwlog
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR
  )
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/lwlog/lwlog-version.cmake
  COMPATIBILITY AnyNewerVersion)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/lwlog/lwlog-version.cmake
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_CMAKEDIR}/lwlog/lwlog-config.cmake
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR}/lwlog)

if(LWLOG_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
