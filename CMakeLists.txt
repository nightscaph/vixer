cmake_minimum_required (VERSION 2.8)
project (vixer)

set (CMAKE_CXX_FLAGS "-std=c++11")
aux_source_directory (./src SRC)
message (STATUS "BINARY" ${PROJECT_BINARY_DIR})
message (STATUS "SOURCE" ${PROJECT_SOURCE_DIR})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SRC})
