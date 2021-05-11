message("In Main/CMakeLists.txt >>>>>>>>>>")

cmake_minimum_required(VERSION 3.17)

project(CppPractice VERSION 1.0.3)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
#ADD_DEFINITIONS(-DWIN32 -D_WIN32)

IF (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    add_compile_options()
ELSE ()
    add_compile_options(-Wno-unused-variable -Wno-unused-parameter -Wno-unused-value)
ENDIF ()

add_subdirectory(PureC)
add_subdirectory(CppPrimerPlus)

message("PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

MESSAGE(STATUS "CMAKE_SYSTEM is ${CMAKE_SYSTEM}")
MESSAGE(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    MESSAGE(STATUS "current platform: Linux ")
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    MESSAGE(STATUS "current platform: Windows")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF ()

IF (WIN32)
    MESSAGE(STATUS "Now is windows")
ELSEIF (APPLE)
    MESSAGE(STATUS "Now is Apple systems.")
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's.")
ENDIF ()

message("CMAKE_C_COMPILER_ID=${CMAKE_C_COMPILER_ID} arch=${CMAKE_C_COMPILER_ARCHITECTURE_ID} version=${CMAKE_C_COMPILER_VERSION}")
message("CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID} arch=${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} version=${CMAKE_CXX_COMPILER_VERSION} internal=${CMAKE_CXX_COMPILER_VERSION_INTERNAL} target=${CMAKE_CXX_COMPILER_TARGET} abi=${CMAKE_CXX_COMPILER_ABI}")

if (WIN32)
    message("window USERPROFILE=$ENV{USERPROFILE}")   #C:\Users\xxx
    message("window APPDATA=$ENV{APPDATA}")           #C:\Users\xxx\AppData\Roaming
    message("window LOCALAPPDATA=$ENV{LOCALAPPDATA}") #C:\Users\xxx\AppData\Local
endif ()

set(CMAKE_INSTALL_PREFIX "./TestInstall")

set(CTest_VERSION_MAJOR 1)
set(CTest_VERSION_MINOR 2)
set(CTest_VERSION_PATCH 3)

option(USE_MYMATH "Use my kai's math implementation" ON)


# does this system provide the log and exp functions?
include(CheckSymbolExists)
check_symbol_exists(log "math.h" HAVE_LOG)
check_symbol_exists(exp "cmath" HAVE_EXP)

message("HAVE_LOG=${HAVE_LOG}")
message("HAVE_EXP=${HAVE_EXP}")

if (NOT (HAVE_LOG AND HAVE_EXP))
    message("NO log and exp")
endif ()

configure_file(
        "${PROJECT_SOURCE_DIR}/CTestConfig.h.in"
        "${PROJECT_BINARY_DIR}/CTestConfig.h"
)

include_directories("${PROJECT_BINARY_DIR}")

message("before EXTRA_LIBS: ${EXTRA_LIBS}")

if (USE_MYMATH)
    include_directories("${PROJECT_SOURCE_DIR}/MathFunctions")
    add_subdirectory(MathFunctions)
    set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
    #message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
endif (USE_MYMATH)

message("after: ${EXTRA_LIBS}")

add_subdirectory(ModernCpp)

if (WIN32)
    add_subdirectory(DllFunc)
    AUX_SOURCE_DIRECTORY(./WinApi WINAPI_DIR_SRCS)
    set(WIN_LIBS ${WIN_LIBS} DllFunc)
endif ()

#include_directories(${PROJECT_SOURCE_DIR}/ModernCpp)

AUX_SOURCE_DIRECTORY(./UseMathFunctions USE_MATH_FUNCTION_DIR_SRCS)
message("USE_MATH_FUNCTION_DIR_SRCS=${USE_MATH_FUNCTION_DIR_SRCS}")

#当前目录下所有源文件赋给DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
message("DIR_SRCS=${DIR_SRCS}")

add_executable(cpp_practice ${DIR_SRCS} ${USE_MATH_FUNCTION_DIR_SRCS} ${WINAPI_DIR_SRCS})

target_link_libraries(cpp_practice libModernCpp ${EXTRA_LIBS} ${WIN_LIBS})


install(TARGETS cpp_practice DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/CTestConfig.h"
        DESTINATION include)

enable_testing()

add_test(CTestRuns cpp_practice 25)
set_tests_properties(CTestRuns PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")

add_test(CTestNegative cpp_practice -25)
set_tests_properties(CTestNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is -nan")

add_test(CTestSmall cpp_practice 0.01)
set_tests_properties(CTestSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.01 is 0.1")

add_test(CTestUsage cpp_practice)
set_tests_properties(CTestUsage PROPERTIES PASS_REGULAR_EXPRESSION "number")

#define a macro to simplify adding tests, then use it
macro(do_test arg result)
    add_test(CTestComp${arg} cpp_practice ${arg})
    set_tests_properties(CTestComp${arg} PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro(do_test)

# do a bunch of result based tests
do_test(16 "16 is 4")
do_test(abc "0 is 0")

# build a CPack driven installer package
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP")
set(CPACK_SOURCE_GENERATOR "7Z")
set(CPACK_SOURCE_IGNORE_FILES "cmake-build*" ".idea*" ".gitignore" ".git" "*.zip" "*.7z")

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${CTEST_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CTEST_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CTEST_VERSION_PATCH}")
include(CPack)

message("out Main/CMakeLists.txt <<<<<<<<<<")
