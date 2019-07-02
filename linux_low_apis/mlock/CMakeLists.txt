cmake_minimum_required (VERSION 2.6)
project (mlock)

INCLUDE_DIRECTORIES(
    ../../lib
)


SET(
    SOURCES

    ../../lib/base.cpp
    ../../lib/func_trace.cpp
    mlock.cpp
)

add_executable(mlock ${SOURCES})

INSTALL(TARGETS mlock
    RUNTIME DESTINATION bin
)