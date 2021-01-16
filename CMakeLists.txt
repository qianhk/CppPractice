cmake_minimum_required(VERSION 3.17)
project(CppPractice)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ModernCpp)

#include_directories(${PROJECT_SOURCE_DIR}/ModernCpp)

#当前目录下所有源文件赋给DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
message("DIR_SRCS=${DIR_SRCS}")

#// main.cpp Shape.cpp Shape.h virtual_derived.h FileOperate.cpp FileOperate.h Temple.hpp Temple.h Thread.cpp Thread.h ModelCxx.cpp ModelCxx.h
add_executable(cpp_practice ${DIR_SRCS})

target_link_libraries(cpp_practice libModernCpp)
