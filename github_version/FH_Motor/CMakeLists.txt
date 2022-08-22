cmake_minimum_required(VERSION 3.16)
project(FH_Motor)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

include_directories(include)
#find
find_package(Threads REQUIRED)

add_subdirectory(pybind11)
aux_source_directory(src SOURCE)
pybind11_add_module(FH_Motor
        ${SOURCE})

target_link_libraries(FH_Motor PRIVATE Threads::Threads)#need private

