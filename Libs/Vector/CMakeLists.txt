cmake_minimum_required(VERSION 3.23)
project(Vector)

set(CMAKE_CXX_STANDARD 14)

add_library(Vector SHARED Vector.cpp Vector.h)
include_directories(../Number)


find_library(NUMBER_LIB libLib.a ../Number/cmake-build-debug)
target_link_libraries(Vector LINK_PUBLIC ${NUMBER_LIB})
