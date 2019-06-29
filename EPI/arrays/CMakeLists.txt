cmake_minimum_required (VERSION 2.6)
project (basic_unique_ptr)

INCLUDE_DIRECTORIES(
    #../../lib
)


add_executable(compute_the_max_difference compute_the_max_difference.cpp)

INSTALL(TARGETS compute_the_max_difference
    RUNTIME DESTINATION bin
)