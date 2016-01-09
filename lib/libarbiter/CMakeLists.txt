set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/player_list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/player.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/player_list.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cc
)

add_library(arbiter SHARED ${SOURCES} ${HEADERS})
set_target_properties(arbiter PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(arbiter PUBLIC -std=c++11 -Wall -Werror -Wextra -W)
target_include_directories(arbiter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
