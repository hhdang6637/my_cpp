cmake_minimum_required (VERSION 2.6)
project (cpp)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

add_subdirectory(smart_pointer)
add_subdirectory(special_containers)
add_subdirectory(EPI)
add_subdirectory(linux_low_apis)
add_subdirectory(exception)
add_subdirectory(vtable_vptr)
