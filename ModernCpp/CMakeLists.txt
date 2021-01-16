
aux_source_directory(. DIR_MODERN_CPP_SRCS)
message("in ModernCpp/CMakeLists.txt DIR_MODERN_CPP_SRCS=${DIR_MODERN_CPP_SRCS}")
add_library(libModernCpp ${DIR_MODERN_CPP_SRCS})
