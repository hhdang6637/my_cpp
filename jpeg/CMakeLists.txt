cmake_minimum_required (VERSION 2.6)
project (jpeg_learning)

INCLUDE_DIRECTORIES()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

add_executable(jpeg_learning jpeg_learning.cpp)

INSTALL(TARGETS jpeg_learning
    RUNTIME DESTINATION .
)
