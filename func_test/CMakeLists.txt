cmake_minimum_required(VERSION 3.22)
project(func_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(func_test main.cpp MiniPID.h MiniPID.cpp)
