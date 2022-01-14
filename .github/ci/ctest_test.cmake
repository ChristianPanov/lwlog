include(${CMAKE_CURRENT_LIST_DIR}/configure_github_actions.cmake)

ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")

# Pick up from where build left off
ctest_start(APPEND)

ctest_test(APPEND
  RETURN_VALUE test_result)

if (test_result)
  message(FATAL_ERROR "Failed to test")
endif ()
