# Lists file to be used by the developer for the best IDE discoverability
cmake_minimum_required(VERSION 3.14)

project(lwlog_all CXX)

# Set our own release build flags
if(MSVC)
  # Default flags from the VS generator are: /MD /O2 /Ob2 /DNDEBUG
  set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Oi /DNDEBUG" CACHE INTERNAL "")
else()
  message(FATAL_ERROR "TODO: support for platforms other than Windows")
endif()

set(lwlog_INCLUDE_WITHOUT_SYSTEM YES CACHE INTERNAL "")

include(FetchContent)
FetchContent_Declare(lwlog SOURCE_DIR "${PROJECT_SOURCE_DIR}/..")
FetchContent_Declare(sandbox SOURCE_DIR "${PROJECT_SOURCE_DIR}/../sandbox")
FetchContent_MakeAvailable(lwlog sandbox)
