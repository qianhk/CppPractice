cmake_minimum_required(VERSION 3.17)
project(testDemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(testDemo main.cpp Shape.cpp Shape.h virtual_derived.h FileOperate.cpp FileOperate.h Temple.hpp Temple.h Thread.cpp Thread.h ModelCxx.cpp ModelCxx.h)