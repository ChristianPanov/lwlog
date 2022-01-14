include(${CMAKE_CURRENT_LIST_DIR}/configure_github_actions.cmake)

set(cmake_args -DLWLOG_BUILD_EXAMPLES:BOOL=ON -DENABLE_TESTING:BOOL=ON)

ctest_start("Continuous" TRACK "Experimental")

# Update the branch to the latest
find_package(Git)
set(CTEST_UPDATE_VERSION_ONLY ON)
set(CTEST_UPDATE_COMMAND "${GIT_EXECUTABLE}")
ctest_update()

# Run configuration
ctest_configure(
  OPTIONS "${cmake_args}"
  RETURN_VALUE configure_result)

ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")

if (configure_result)
  message(FATAL_ERROR
    "Failed to configure")
endif ()
