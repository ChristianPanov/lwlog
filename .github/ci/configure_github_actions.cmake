if (DEFINED "ENV{GITHUB_ACTIONS}")
  set(CTEST_SITE "github-actions")
else ()
  message(WARNING "This script is being run outside of a GitHub Actions environment")

  get_filename_component(project_root_dir "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
  set(ENV{GITHUB_WORKSPACE} ${project_root_dir})
endif ()

set(CTEST_SOURCE_DIRECTORY "$ENV{GITHUB_WORKSPACE}")
set(CTEST_BINARY_DIRECTORY "${CTEST_SOURCE_DIRECTORY}/build")

set(CTEST_BUILD_NAME "lwlog-ci")

if (ENV{CMAKE_BUILD_TYPE})
  set(CTEST_BUILD_CONFIGURATION "$ENV{CMAKE_BUILD_TYPE}")
endif ()

if (ENV{CMAKE_GENERATOR})
  set(CTEST_CMAKE_GENERATOR "$ENV{CMAKE_GENERATOR}")
else ()
  set(CTEST_CMAKE_GENERATOR "Ninja")
endif ()

if (NOT DEFINED ENV{CTEST_MAX_PARALLELISM})
  set(ENV{CTEST_MAX_PARALLELISM} 2)
endif ()

set(CTEST_TEST_TIMEOUT 50)
