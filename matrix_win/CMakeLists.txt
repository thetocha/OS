cmake_minimum_required(VERSION 3.20)
project(matrix_win)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix_win main.cpp matrix.cpp matrix.h blockMatrix.cpp blockMatrix.h)
