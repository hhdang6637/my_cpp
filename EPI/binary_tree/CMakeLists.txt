cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)

add_executable(problem6_1 problem6_1.cpp)

INSTALL(TARGETS problem6_1
    RUNTIME DESTINATION bin
)