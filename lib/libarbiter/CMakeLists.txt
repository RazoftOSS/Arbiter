set(CMAKE_BUILD_TYPE Debug)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/game.h
    ${CMAKE_CURRENT_SOURCE_DIR}/player.h
    ${CMAKE_CURRENT_SOURCE_DIR}/player_list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/swiss_pairer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/swiss_pair_table.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/player.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/player_list.cc
)

find_package(Boost COMPONENTS log REQUIRED)
add_library(arbiter SHARED ${SOURCES} ${HEADERS})
add_definitions(-DBOOST_ALL_DYN_LINK)
set_target_properties(arbiter PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(arbiter PUBLIC -std=c++11 -Wall -Werror -Wextra -Wpedantic)
target_link_libraries(arbiter PUBLIC ${Boost_LIBRARIES})
target_include_directories(arbiter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)
