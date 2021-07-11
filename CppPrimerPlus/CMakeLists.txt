cmake_minimum_required(VERSION 3.17)

project(CppPrimerPlus)

#add_compile_options(-stdlib=libc++) # c、c++均生效
#ADD_DEFINITIONS("-stdlib=libc++") # c、c++均生效
#set(CMAKE_C_FLAGS "-stdlib=libc++") # c均生效
#set(CMAKE_CXX_FLAGS "-stdlib=libc++") # c++生效
#add_compile_options(-g)

add_executable(${PROJECT_NAME} main.cpp baseclass.cpp baseclass.h templateclass.hpp exceptiondemo.cpp exceptiondemo.h rttidemo.cpp rttidemo.h stltest.cpp stltest.h)
