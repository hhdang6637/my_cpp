cmake_minimum_required (VERSION 2.6)
project (mlock)

INCLUDE_DIRECTORIES(
    ../../lib
)


SET(
    SOURCES

    ../../lib/base.cpp
    ../../lib/func_trace.cpp
    pipe.cpp
)

ADD_EXECUTABLE(pipe ${SOURCES})


TARGET_LINK_LIBRARIES(
    pipe

    -lpthread
)


INSTALL(TARGETS pipe
    RUNTIME DESTINATION bin
)
