cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


SET(
    SOURCES

    ../../lib/func_trace.cpp
    basic_unique_ptr.cpp
)

add_executable(basic_unique_ptr ${SOURCES})