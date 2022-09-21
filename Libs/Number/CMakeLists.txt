cmake_minimum_required(VERSION 3.23)
project(Number)

set(CMAKE_CXX_STANDARD 14)

add_executable(Number main.cpp Number.h Number.cpp)
add_library(Lib Number.h Number.cpp)