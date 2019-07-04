cmake_minimum_required (VERSION 2.6)
project (vtable_vptr)

INCLUDE_DIRECTORIES(
    ../lib
)


SET(
    SOURCES

    ../lib/base.cpp
    ../lib/func_trace.cpp
    vtable_vptr.cpp
)

add_executable(vtable_vptr ${SOURCES})

INSTALL(TARGETS vtable_vptr
    RUNTIME DESTINATION bin
)