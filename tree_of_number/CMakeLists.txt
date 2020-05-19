cmake_minimum_required (VERSION 2.6)
project (tree_of_number)

INCLUDE_DIRECTORIES()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

add_executable(tree_of_number tree_of_number.cpp)

INSTALL(TARGETS tree_of_number
    RUNTIME DESTINATION .
)
