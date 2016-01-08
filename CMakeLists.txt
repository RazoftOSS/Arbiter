cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(arbiter)

set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libarbiter)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/libarbiter)

enable_testing(true)
add_test(libarbiter_test_all ${CMAKE_BINARY_DIR}/test/libarbiter/libarbiter_test)
