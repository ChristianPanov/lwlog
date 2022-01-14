cmake_minimum_required(VERSION 3.16)
project(lwlog
  LANGUAGES CXX
  DESCRIPTION "Light Weight Logging Library"
  HOMEPAGE_URL "https://github.com/ChristianPanov/lwlog"
  VERSION 1.0.0)

option(LWLOG_BUILD_EXAMPLES "Build example program" ON)
option(ENABLE_TESTING "Enable tests (implicitly builds examples)" ON)
option(LWLOG_USE_LOCALTIME "Use the local time instead of GMT" OFF)

include(GNUInstallDirs)
set(CMAKE_INSTALL_CMAKEDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

find_package(Threads REQUIRED)

add_subdirectory(lwlog)

# Install Package
include(CMakePackageConfigHelpers)
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
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR})

if (ENABLE_TESTING)
  enable_testing()
endif ()

if(LWLOG_BUILD_EXAMPLES OR ENABLE_TESTING)
  add_subdirectory(examples)
endif()
