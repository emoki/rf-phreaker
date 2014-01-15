cmake_minimum_required (VERSION 2.8)

project (gsm_layer_3_library)

# gsm_layer_3_library version number.
# TODO - finish this when you have time!
set (gsm_layer_3_library_VERSION_MAJOR 1)
set (gsm_layer_3_library_VERSION_MINOR 0)
set (gsm_layer_3_library_VERSION_PATCH 0)
set (gsm_layer_3_library_VERSION_TWEAK 0)

file (GLOB glob_SRCS *.cpp *.h)

set (gsm_layer_3_library_SRCS
	${glob_SRCS}
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (gsm_layer_3_library ${gsm_layer_3_library_SRCS})

target_link_libraries (gsm_layer_3_library common)
