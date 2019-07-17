cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


add_executable(problem4_1 problem4_1.cpp ../../lib/base.cpp)

INSTALL(TARGETS problem4_1
    RUNTIME DESTINATION bin
)

