message("In MathFunctions/CMakeLists.txt >>>>>>>>>>")

#set(CMAKE_INSTALL_PREFIX "YYY")
#message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

# first we add the executable that generates the table
add_executable(MakeTable MakeTable.cpp)

message("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message("CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")

# add the command to generate the source code
add_custom_command (
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        DEPENDS MakeTable
)

# add the binary tree directory to the search path for
# include files
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )


# add the main library
#add_library(MathFunctions mysqrt.cpp)
add_library(MathFunctions mysqrt.cpp ${CMAKE_CURRENT_BINARY_DIR}/Table.h  )

install(TARGETS MathFunctions DESTINATION bin)
install(FILES mysqrt.h DESTINATION include)

message("out MathFunctions/CMakeLists.txt <<<<<<<<<<")
