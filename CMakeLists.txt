cmake_minimum_required(VERSION 3.22)
project(FH_Motor)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

# serial库文件路径
set(LIB_DIR /usr/local/include)
set(LIB_DIR /usr/local/lib)
set(CMAKE_PREFIX_PATH   "/home/zz23ecl/anaconda3/envs/MotionControl")

#find
find_package(Threads REQUIRED)
find_package(Python 3.8.8 COMPONENTS Interpreter Development REQUIRED)

include_directories(${LIB_DIR})
add_subdirectory(pybind11)

pybind11_add_module(FH_Motor SHARED Control.cpp RS232.cpp MiniPID.cpp)

target_link_libraries(FH_Motor PRIVATE ${LIB_DIR}/libCppLinuxSerial.a Threads::Threads)#need private

target_include_directories(FH_Motor PRIVATE ${PYTHON3_INC_DIR})