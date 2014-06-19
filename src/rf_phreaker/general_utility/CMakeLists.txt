

project (general_utility)

# general_utility version number.
# TODO - finish this when you have time!
set (general_utility_VERSION_MAJOR 1)
set (general_utility_VERSION_MINOR 0)
set (general_utility_VERSION_PATCH 0)
set (general_utility_VERSION_TWEAK 0)

# Set the source files.
set (general_utility_SRCS 
	general_utility.cpp
	calibration.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_definitions (/DTBB_PREVIEW_GRAPH_NODES)

add_executable (general_utility ${general_utility_SRCS})

target_link_libraries (general_utility processing)
target_link_libraries (general_utility qt_specific)
