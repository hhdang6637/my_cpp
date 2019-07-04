cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


SET(
    SOURCES

    ../../lib/base.cpp
    ../../lib/func_trace.cpp
    exception_in_destructor.cpp
)

add_executable(exception_in_destructor ${SOURCES})

INSTALL(TARGETS exception_in_destructor
    RUNTIME DESTINATION bin
)