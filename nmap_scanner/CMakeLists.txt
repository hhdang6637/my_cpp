cmake_minimum_required (VERSION 2.6)
project (nmap_scanner)

INCLUDE_DIRECTORIES(
#    ../../lib
)


SET(
    SOURCES

#    ../../lib/base.cpp
#    ../../lib/func_trace.cpp
    main.cpp
    network.cpp
)

ADD_EXECUTABLE(nmap_scaner ${SOURCES})


TARGET_LINK_LIBRARIES(
    nmap_scaner

    -lpthread
)


INSTALL(TARGETS nmap_scaner
    RUNTIME DESTINATION bin
)
