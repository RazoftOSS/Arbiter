include_directories(
  ${CMAKE_SOURCE_DIR}/extern/catch/single_include
)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cc
)

add_executable(libarbiter_test ${SOURCES})
set_target_properties(libarbiter_test PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(libarbiter_test arbiter)
