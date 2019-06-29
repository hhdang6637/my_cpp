cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


add_executable(problem5_1 problem5_1.cpp)

INSTALL(TARGETS problem5_1
    RUNTIME DESTINATION bin
)