
#//CMakeLists.txt编写常用命令
#//https://www.cnblogs.com/xl2432/p/11225276.html

#//CMake 复制文件方法
#//https://www.cnblogs.com/JoyPoint/p/11629521.html

message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("lookKai cmake build type: Debug")
elseif (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    message("lookKai cmake build type: RelWithDebInfo")
else ()
    message("lookKai cmake build type: Other Unknown")
endif ()

#aux_source_directory(. DIR_DllFunc_SRCS)
#
#message("in DllFunc/CMakeLists.txt DIR_DllFunc_SRCS=${DIR_DllFunc_SRCS}")
#
#add_library(DllFunc ${DIR_DllFunc_SRCS})

#cmake_minimum_required(VERSION 3.17)
project(DllFunc)
#
#set(CMAKE_CXX_STANDARD 14)
#message("lookKai PROJECT_NAME=${PROJECT_NAME}")
#add_library(${PROJECT_NAME} library.cpp library.h)

ADD_DEFINITIONS(-DKAI_DLL_EXPORTS)

add_library(${PROJECT_NAME} SHARED library.cpp library.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}$<$<CONFIG:Debug>:d>")

#一般将此内容放在lib子项目的CMakelists.txt的最后，该方法采用POST_BUILD，所以需注意要复制的源应该是一个固定字符串，而不能用FILE GLOB的方法，因为在编译前该源为空，在VS中会出现MSB3073错误，提示copy from 为空值。
SET(Plugins_TEST_Debug_DLL_FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}d.dll
        )
SET(Plugins_TEST_Release_DLL_FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.dll
        )

add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E
        copy_if_different
        "$<$<CONFIG:RelWithDebInfo>:${Plugins_TEST_Release_DLL_FILE}>"
        "$<$<CONFIG:Debug>:${Plugins_TEST_Debug_DLL_FILE}>"
        "${CMAKE_BINARY_DIR}/"
        )
