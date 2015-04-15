

project (processing)

# processing version number.
# TODO - finish this when you have time!
set (processing_VERSION_MAJOR 1)
set (processing_VERSION_MINOR 0)
set (processing_VERSION_PATCH 0)
set (processing_VERSION_TWEAK 0)

# Set the source files.
set (processing_SRCS 
	collection_info.cpp
	collection_info.h
	collection_info_container.h
	collection_manager_body.h
	gps_body.h
	gps_graph.h
	frequency_correction_body.h
	frequency_correction_calculator.h
	frequency_correction_graph.cpp
	frequency_correction_graph.h
	frequency_range_creation.h
	layer_3_tracker.h
	lte_output_and_feedback_body.h
	lte_processing_body.h
	measurement_conversion.h
	node_defs.h
	data_output.h
	data_output_async.h
	processing_graph.cpp
	processing_graph.h
	scanner_error_tracker.h
	scanner_io.h
	switch_body.h
	umts_output_and_feedback_body.h
	umts_processing_body.h
	processing_utility.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_definitions (/DTBB_PREVIEW_GRAPH_NODES)

add_library (processing STATIC ${processing_SRCS})

target_link_libraries (processing scanner)
target_link_libraries (processing umts_analysis)
target_link_libraries (processing lte_analysis)
