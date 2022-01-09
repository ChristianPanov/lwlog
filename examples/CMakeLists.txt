add_executable(sandbox Sandbox.cpp)
target_link_libraries(sandbox PRIVATE lwlog::lwlog)

if (ENABLE_TESTING)
  add_test(
    NAME sandbox
    COMMAND sandbox)
endif ()
