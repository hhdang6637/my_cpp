cmake_minimum_required (VERSION 2.6)
project (vtable_vptr)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -g")

INCLUDE_DIRECTORIES(
    ../lib
)

add_executable(vtable_basic ../lib/base.cpp ../lib/func_trace.cpp vtable_basic.cpp)

INSTALL(TARGETS vtable_basic RUNTIME DESTINATION bin )

add_executable(vtable_basic_2 ../lib/base.cpp ../lib/func_trace.cpp vtable_basic_2.cpp)

INSTALL(TARGETS vtable_basic_2 RUNTIME DESTINATION bin )

add_executable(vtable_basic_3 ../lib/base.cpp ../lib/func_trace.cpp vtable_basic_3.cpp)

INSTALL(TARGETS vtable_basic_3 RUNTIME DESTINATION bin )