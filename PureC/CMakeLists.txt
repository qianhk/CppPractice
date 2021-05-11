cmake_minimum_required(VERSION 3.17)

project(PureCDemo C)

#set(CMAKE_C_STANDARD 11)
message("CMAKE_C_STANDARD=${CMAKE_C_STANDARD} CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")

add_executable(PureCDemo main.c)
