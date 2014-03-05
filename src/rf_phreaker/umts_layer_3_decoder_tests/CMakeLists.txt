

project (umts_layer_3_decoder_tests)

# umts_layer_3_decoder_tests version number.
# TODO - finish this when you have time!
set (umts_layer_3_decoder_tests_VERSION_MAJOR 1)
set (umts_layer_3_decoder_tests_VERSION_MINOR 0)
set (umts_layer_3_decoder_tests_VERSION_PATCH 0)
set (umts_layer_3_decoder_tests_VERSION_TWEAK 0)

set (umts_layer_3_decoder_tests_SRCS 
	test_bit_stream_container.cpp
	test_bit_stream_container.h
	test_segmented_sib.cpp
	test_segmented_sib.h
	umts_layer_3_decoder_tests.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/asn1_types.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/umts_rrc_asn_library")
include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/umts_layer_3_decoder")

add_executable (umts_layer_3_decoder_tests ${umts_layer_3_decoder_tests_SRCS})

target_link_libraries (umts_layer_3_decoder_tests layer_3_common)
target_link_libraries (umts_layer_3_decoder_tests umts_layer_3_decoder)
target_link_libraries (umts_layer_3_decoder_tests umts_rrc_asn_library)
target_link_libraries (umts_layer_3_decoder_tests gmock)