cmake_minimum_required (VERSION 2.8)

project (lte_layer_3_decoder_tests)

# lte_layer_3_decoder_tests version number.
# TODO - finish this when you have time!
set (lte_layer_3_decoder_tests_VERSION_MAJOR 1)
set (lte_layer_3_decoder_tests_VERSION_MINOR 0)
set (lte_layer_3_decoder_tests_VERSION_PATCH 0)
set (lte_layer_3_decoder_tests_VERSION_TWEAK 0)

set (lte_layer_3_decoder_tests_SRCS 
	lte_decoding_tests.cpp
	lte_decoding_tests.h
	lte_layer_3_decoder_tests.cpp
	lte_sib_1.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/lte_rrc_asn_library")
include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/lte_layer_3_decoder")

add_executable (lte_layer_3_decoder_tests ${lte_layer_3_decoder_tests_SRCS})

target_link_libraries (lte_layer_3_decoder_tests layer_3_common)
target_link_libraries (lte_layer_3_decoder_tests lte_layer_3_decoder)
target_link_libraries (lte_layer_3_decoder_tests gmock)