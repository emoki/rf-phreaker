

project (lte_analysis)

# lte_analysis version number.
# TODO - finish this when you have time!
set (lte_analysis_VERSION_MAJOR 1)
set (lte_analysis_VERSION_MINOR 0)
set (lte_analysis_VERSION_PATCH 0)
set (lte_analysis_VERSION_TWEAK 0)

# Set the source files.
set (lte_analysis_SRCS 
	cc_tb.c
	cc_tb.h
	crc.c
	crc.h
	lte_analysis.cpp
	lte_analysis.h
	lte_analysis_impl.cpp
	lte_analysis_impl.h
	lte_cell_search.cpp
	lte_channel_estimation.cpp
	lte_channel_estimation.h
	lte_common.cpp
	lte_common.h
	lte_config.h
	lte_crc_16.c
	lte_crc_16.h
	lte_decode_data.cpp
	lte_decode_data.h
	lte_errors.h
	lte_fft.cpp
	lte_fft.h
	lte_io.h
	lte_measurement.h
	lte_pbch.cpp
	lte_pbch.h
	lte_pcfich.cpp
	lte_pcfich.h
	lte_pdcch.cpp
	lte_pdcch.h
	lte_pdcch_dci_table.h
	lte_pdsch.cpp
	lte_pdsch.h
	lte_pss.cpp
	lte_pss.h
	lte_synchronization.cpp
	lte_synchronization.h
	lte_turbo_code.cpp
	lte_turbo_code.h
	lte_turbo_code_rate_match.cpp
	lte_turbo_code_rate_match.h
	lte_types.h
	pbch_interleaver_idx.h
	q_channel.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (lte_analysis SHARED ${lte_analysis_SRCS})

target_link_libraries (lte_analysis common)
target_link_libraries (lte_analysis ipp_custom)
target_link_libraries (lte_analysis fir_filter)
target_link_libraries (lte_analysis ${TBB_LIBRARY})
target_link_libraries (lte_analysis lte_layer_3_decoder)
target_link_libraries (lte_analysis ${Boost_LIBRARIES})
