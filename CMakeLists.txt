##
# @brief brief
# @version 1.0
# @author Night
# @email email
# @company company
# @date 2018-02-27 06:17:35
##

cmake_minimum_required (VERSION 2.8)
project (vixer)

set (CMAKE_CXX_FLAGS "-std=c++11")

if (UNIX OR MINGW)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
elseif (WIN32)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif ()

set(_HEADERS_FLAG *.h *.hpp *.hxx)
set(_SOURCES_FLAG *.cc *.cpp *.cxx)
set(_SOURCE_DIR "src")
#set_target_properties(target PROPERTIES COMPILE_FLAGS “/EHsc")
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${_SOURCE_DIR})

add_definitions(-DOPENSSL_PATH)

message (STATUS "----[OPENSSL_PATH] -> " ${OPENSSL_PATH})

macro(_set_profile src_dir)
	foreach(_f ${ARGN})
		list(LENGTH ${_f} _l)
		MATH(EXPR _l "${_l} - 1")
		
		foreach(index RANGE ${_l})
			list(GET ${_f} 0 _v)
			list(REMOVE_AT ${_f} 0)
			list(APPEND ${_f} "${src_dir}/${_v}")
		endforeach(index)
		
		file(GLOB_RECURSE _F ${${_f}})
		list(APPEND _FILES ${_F})
	endforeach(_f)
	
	foreach(_f ${_FILES})
		get_filename_component(_d ${_f} DIRECTORY)
		file(RELATIVE_PATH _rd ${PROJECT_SOURCE_DIR} ${_d})
		string(REPLACE "/" "\\" _rd_r ${_rd})
		source_group(${_rd_r} FILES ${_f})
		message (STATUS "----[source file] -> :" ${_f})
	endforeach(_f)		
endmacro(_set_profile)

_set_profile(${_SOURCE_DIR} _HEADERS_FLAG _SOURCES_FLAG)

include_directories(${OPENSSL_PATH}/include)
link_directories(${OPENSSL_PATH}/lib)

link_libraries(ssl crypto)

add_executable(${PROJECT_NAME} ${_FILES})
