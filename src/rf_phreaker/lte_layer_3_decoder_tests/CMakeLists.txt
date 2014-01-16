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
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/asn1_config.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/asn1_types.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.cpp
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/decode_support_functions.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/pdu_element.cpp
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/pdu_element.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/per_decoder_container.cpp
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/per_decoder_container.h
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/per_decoder_interface.cpp
	${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/layer_3_decoder_common/per_decoder_interface.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories ("${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/lte_rrc_asn_library")
include_directories ("${RF_PHREAKER_ROOT_PATH}/src/rf_phreaker/lte_layer_3_decoder")

add_executable (lte_layer_3_decoder_tests ${lte_layer_3_decoder_tests_SRCS})

target_link_libraries (lte_layer_3_decoder_tests layer_3_common)
target_link_libraries (lte_layer_3_decoder_tests lte_layer_3_decoder)
target_link_libraries (lte_layer_3_decoder_tests gmock)