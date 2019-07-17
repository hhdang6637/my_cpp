cmake_minimum_required (VERSION 2.6)
project (nmap_scanner)

INCLUDE_DIRECTORIES(
#    ../
)


SET(
    SOURCES

#    ../../lib/base.cpp
#    ../../lib/func_trace.cpp
    main.cpp
    network.cpp
    nmap_scanner.cpp
)

ADD_EXECUTABLE(nmap_scanner ${SOURCES})


TARGET_LINK_LIBRARIES(
    nmap_scanner

    #-lpthread
)


INSTALL(TARGETS nmap_scanner
    RUNTIME DESTINATION bin
)
