set(CMAKE_BUILD_TYPE Debug)

include_directories(
  ${CMAKE_SOURCE_DIR}/extern/catch/single_include
  ${Boost_INCLUDE_DIRS}
)

set(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/player_list_test.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/player_test.cc
)

set(MISC_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/player_list_test.csv
  ${CMAKE_CURRENT_SOURCE_DIR}/player_list_test.json
)

add_executable(libarbiter_test ${SOURCES})
set_target_properties(libarbiter_test PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(libarbiter_test PUBLIC -std=c++11 -Wall -Werror -Wextra
  -Wpedantic)
target_link_libraries(libarbiter_test arbiter)
file(COPY ${MISC_FILES} DESTINATION ${CMAKE_BINARY_DIR}/test/libarbiter)
