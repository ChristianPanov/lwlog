if(NOT LWLOG_BUILD_EXAMPLES)
    return()
endif()

add_executable(sandbox Sandbox.cpp)
target_link_libraries(sandbox PRIVATE lwlog::lwlog)
