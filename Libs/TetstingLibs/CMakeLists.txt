cmake_minimum_required(VERSION 3.23)
project(TetstingLibs)

set(CMAKE_CXX_STANDARD 14)

include_directories(../Number ../Vector)

find_library(NUMBER_LIB libLib.a ../Number/cmake-build-debug)
find_library(VECTOR libVector.so ../Vector/cmake-build-debug)

add_executable(TetstingLibs main.cpp)
target_link_libraries(TetstingLibs LINK_PUBLIC ${NUMBER_LIB})
target_link_libraries(TetstingLibs LINK_PUBLIC ${VECTOR})
