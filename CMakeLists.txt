cmake_minimum_required(VERSION 3.12)

project(lwlog
        VERSION 0.0.1
        DESCRIPTION "Very fast C++17 logging library"
        HOMEPAGE_URL "https://github.com/ChristianPanov/lwlog"
        LANGUAGES CXX)

# ---- Warning guard ----

# Protect dependents from this project's warnings if the guard isn't disabled
set(lwlog_warning_guard SYSTEM)
if(lwlog_INCLUDE_WITHOUT_SYSTEM)
  set(lwlog_warning_guard "")
endif()

# ---- Declare library ----

set(headers
        include/lwlog/details/color.h
        include/lwlog/details/datetime.h
        include/lwlog/details/file_helper.h
        include/lwlog/details/formatter/formatter.h
        include/lwlog/details/formatter/formatter_data.h
        include/lwlog/details/formatter/formatter_primitives.h
        include/lwlog/details/stream.h
        include/lwlog/fwd.h
        include/lwlog/interface/logger_interface.h
        include/lwlog/interface/sink_interface.h
        include/lwlog/level.h
        include/lwlog/logger.h
        include/lwlog/logger_impl.h
        include/lwlog/lwlog.h
        include/lwlog/policy/log_policy.h
        include/lwlog/policy/sink_color_policy.h
        include/lwlog/policy/sink_storage_policy.h
        include/lwlog/policy/threading_policy.h
        include/lwlog/primitives.h
        include/lwlog/registry.h
        include/lwlog/sinks/file_impl.h
        include/lwlog/sinks/file_sink.h
        include/lwlog/sinks/sink.h
        include/lwlog/sinks/sink_factory.h
        include/lwlog/sinks/sink_impl.h
        include/lwlog/sinks/stderr_color_sink.h
        include/lwlog/sinks/stderr_sink.h
        include/lwlog/sinks/stdout_color_sink.h
        include/lwlog/sinks/stdout_sink.h)

set(sources
        source/details/file_helper.cpp
        source/details/formatter/formatter.cpp
        source/lwlog.cpp
        source/policy/log_policy.cpp
        source/registry.cpp)

add_library(lwlog STATIC ${headers} ${sources})
add_library(lwlog::lwlog ALIAS lwlog)

target_include_directories(lwlog
        ${lwlog_warning_guard}
        PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>")

target_compile_features(lwlog PUBLIC cxx_std_17)

# ---- Install ----

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(lwlog_directory "lwlog-${PROJECT_VERSION}")
set(lwlog_include_directory
        "${CMAKE_INSTALL_INCLUDEDIR}/${lwlog_directory}")

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
        DESTINATION "${lwlog_include_directory}")

install(TARGETS lwlog
        EXPORT lwlogTargets
        ARCHIVE #
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT lwlog_Development
        INCLUDES #
        DESTINATION "${lwlog_include_directory}")

write_basic_package_version_file(
        lwlog-config-version.cmake
        COMPATIBILITY SameMajorVersion)

set(lwlog_install_cmakedir
        "${CMAKE_INSTALL_LIBDIR}/cmake/${lwlog_directory}")

install(FILES "${PROJECT_BINARY_DIR}/lwlog-config-version.cmake"
        DESTINATION "${lwlog_install_cmakedir}")

install(EXPORT lwlogTargets
        FILE lwlog-config.cmake
        NAMESPACE lwlog::
        DESTINATION "${lwlog_install_cmakedir}")
