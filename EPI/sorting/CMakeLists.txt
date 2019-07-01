cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    ../../lib
)


add_executable(sorting sorting.cpp)

INSTALL(TARGETS sorting
    RUNTIME DESTINATION bin
)