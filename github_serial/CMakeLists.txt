cmake_minimum_required(VERSION 3.22)
project(github_serial)

set(CMAKE_CXX_STANDARD 14)

# 库文件路径
set(LIB_DIR /usr/local/include)

set(LIB_DIR /usr/local/lib)

include_directories(${LIB_DIR})

#lib local
add_executable(github_serial main.cpp RS232.cpp MiniPID.h MiniPID.cpp)

find_package(Threads REQUIRED)

target_link_libraries(github_serial ${LIB_DIR}/libCppLinuxSerial.a Threads::Threads)