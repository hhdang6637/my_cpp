cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


add_executable(problem5_2 problem5_2.cpp)

INSTALL(TARGETS problem5_2
    RUNTIME DESTINATION bin
)