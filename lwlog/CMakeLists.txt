file(GLOB_RECURSE headers RELATIVE ${CMAKE_CURRENT_LIST_DIR} CONFIGURE_DEPENDS *.h)
file(GLOB_RECURSE sources RELATIVE ${CMAKE_CURRENT_LIST_DIR} CONFIGURE_DEPENDS *.cpp)

add_library(lwlog ${sources})
add_library(lwlog::lwlog ALIAS lwlog)
target_include_directories(lwlog
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>)
target_link_libraries(lwlog PUBLIC Threads::Threads)
target_compile_features(lwlog PUBLIC cxx_std_17)

configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/options.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/options.h)

# Install headers
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/options.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lwlog)
foreach (header ${headers})
  get_filename_component(directory ${header} DIRECTORY)
  install(FILES ${header}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/lwlog/${directory})
endforeach ()
install(TARGETS lwlog
  EXPORT lwlog_export
  DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT lwlog_export
  DESTINATION ${CMAKE_INSTALL_CMAKEDIR})
