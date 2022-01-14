include(${CMAKE_CURRENT_LIST_DIR}/configure_github_actions.cmake)

ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")

# Pick up from where configure left off
ctest_start(APPEND)

# Run build
ctest_build(
  NUMBER_WARNINGS num_warning 
  RETURN_VALUE build_result)

if (ENV{CTEST_NO_WARNINGS_ALLOWED} AND num_warning GREATER 0)
  message(FATAL_ERROR "Encountered unallowed warnings during build")
endif ()
