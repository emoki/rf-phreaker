cmake_minimum_required (VERSION 2.8)

project (umts_analysis)

# umts_analysis version number.
# TODO - finish this when you have time!
set (umts_analysis_VERSION_MAJOR 1)
set (umts_analysis_VERSION_MINOR 0)
set (umts_analysis_VERSION_PATCH 0)
set (umts_analysis_VERSION_TWEAK 0)

# Set the source files.
set (umts_analysis_SRCS 
	cross_correlation_incoherent_and_coherent_addition.cpp
	cross_correlation_incoherent_and_coherent_addition.h
	cpich_generator.cpp
	cpich_generator.h
	cpich_table_container.cpp
	cpich_table_container.h
	psch_container.cpp
	psch_container.h
	psch_generator.cpp
	psch_generator.h
	sort_peaks.h
	spur_nullifier.cpp
	spur_nullifier.h
	umts_analysis.cpp
	umts_analysis.h
	umts_analysis_impl.cpp
	umts_analysis_impl.h
	umts_bch_decoder.cpp
	umts_bch_decoder.h
	umts_config.h
	umts_measurement.h
	umts_measurement_container.h
	umts_psch_with_brute_force.cpp
	umts_psch_with_brute_force.h
	umts_utilities.h
	umts_types.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (umts_analysis SHARED ${umts_analysis_SRCS})

target_link_libraries (umts_analysis common)
target_link_libraries (umts_analysis ipp_custom)
target_link_libraries (umts_analysis fir_filter)
target_link_libraries (umts_analysis ${TBB_LIBRARY})
target_link_libraries (umts_analysis umts_layer_3_decoder)
target_link_libraries (umts_analysis ${Boost_LIBRARIES})
