cmake_minimum_required (VERSION 2.6)
project (bitsets)

INCLUDE_DIRECTORIES(
    ../../lib
)


SET(
    SOURCES

    ../../lib/base.cpp
    ../../lib/func_trace.cpp
    bitsets.cpp
)

add_executable(bitsets ${SOURCES})

INSTALL(TARGETS bitsets
    RUNTIME DESTINATION bin
)