cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    #../../lib
)


add_executable(problem1_1 problem1_1.cpp)

INSTALL(TARGETS problem1_1
    RUNTIME DESTINATION bin
)