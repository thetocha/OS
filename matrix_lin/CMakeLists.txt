cmake_minimum_required(VERSION 3.23)
project(matrix_lin)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix_lin main.cpp matrix.cpp matrix.h blockMatrix.cpp blockMatrix.h)
