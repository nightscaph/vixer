cmake_minimum_required (VERSION 2.8)
project (vixer)

set (CMAKE_CXX_FLAGS "-std=c++11")

if (UNIX)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif ()

set(_HEADERS_FLAG *.h *.hpp *.hxx)
set(_SOURCES_FLAG *.cc *.cpp *.cxx)
set(_SOURCE_DIR "src")

message (STATUS "---------[_HEADERS_FLAG] -> " ${_HEADERS_FLAG})
message (STATUS "---------[_SOURCES_FLAG] -> " ${_SOURCES_FLAG})

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


add_executable(${PROJECT_NAME} ${_FILES})