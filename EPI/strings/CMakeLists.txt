cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    #../../lib
)


add_executable(problem3_1 problem3_1.cpp)
add_executable(problem3_2 problem3_2.cpp)

INSTALL(TARGETS problem3_1 problem3_2
    RUNTIME DESTINATION bin
)