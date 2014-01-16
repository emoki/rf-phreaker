cmake_minimum_required (VERSION 2.8)

project (processing)

# processing version number.
# TODO - finish this when you have time!
set (processing_VERSION_MAJOR 1)
set (processing_VERSION_MINOR 0)
set (processing_VERSION_PATCH 0)
set (processing_VERSION_TWEAK 0)

# Set the source files.
set (processing_SRCS 
	collection_manager.h
	layer_3_tracker.h
	lte_data_container.h
	processing_graph.cpp
	processing_graph.h
	processing_lte.h
	scanner_io.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (processing STATIC ${processing_SRCS})

target_link_libraries (processing common)
#target_link_libraries (processing bladeRF)
#target_link_libraries (processing ipp_custom)
target_link_libraries (processing scanner)