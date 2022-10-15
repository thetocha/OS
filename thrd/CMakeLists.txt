cmake_minimum_required(VERSION 3.20)
project(thrd)

set(CMAKE_CXX_STANDARD 14)

add_executable(thrd main.cpp matrix.cpp matrix.h blockMatrix.cpp blockMatrix.h)
