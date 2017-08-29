cmake_minimum_required (VERSION 2.8)
project (vixer)

message (STATUS "SYSTEM NAME: " ${CMAKE_SYSTEM_NAME})

set (CMAKE_CXX_FLAGS "-std=c++11")
if (UNIX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

# message (STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS})
aux_source_directory (./src SRC)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} ${SRC})
