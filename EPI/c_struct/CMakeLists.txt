cmake_minimum_required (VERSION 2.6)
project (c_struct)

INCLUDE_DIRECTORIES(
    #../../lib
)


add_executable(c_struct c_struct.cpp)

INSTALL(TARGETS c_struct
    RUNTIME DESTINATION bin
)