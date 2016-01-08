set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.h
)

add_library(arbiter SHARED ${HEADERS})
set_target_properties(arbiter PROPERTIES LINKER_LANGUAGE CXX)
target_compile_options(arbiter PUBLIC -std=c++11 -Wall -Werror -Wextra -W)
target_include_directories(arbiter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
