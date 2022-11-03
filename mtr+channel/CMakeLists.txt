cmake_minimum_required(VERSION 3.20)
project(mtr_channel)

set(CMAKE_CXX_STANDARD 14)

add_executable(mtr_channel main.cpp matrix.cpp matrix.h block_matrix.h block_matrix.cpp channel.h)

