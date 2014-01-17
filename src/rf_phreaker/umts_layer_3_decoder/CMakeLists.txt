cmake_minimum_required (VERSION 2.8)

project (umts_layer_3_decoder)

# umts_layer_3_decoder version number.
# TODO - finish this when you have time!
set (umts_layer_3_decoder_VERSION_MAJOR 1)
set (umts_layer_3_decoder_VERSION_MINOR 0)
set (umts_layer_3_decoder_VERSION_PATCH 0)
set (umts_layer_3_decoder_VERSION_TWEAK 0)

# Set the source files.
set (umts_layer_3_decoder_SRCS 
	asn_type_descriptor.cpp
	asn_type_descriptor.h
	segmented_sib.h
	segmented_sib_container.cpp
	segmented_sib_container.h
	umts_bcch_bch_message.cpp
	umts_bcch_bch_message.h
	umts_layer_3_decoder.cpp
	umts_layer_3_decoder.h
	umts_mib_container.cpp
	umts_mib_container.h
	umts_sib_1_container.cpp
	umts_sib_1_container.h
	umts_sib_3_container.cpp
	umts_sib_3_container.h
	umts_sib_4_container.cpp
	umts_sib_4_container.h		
	umts_sib_11_and_11_bis_container.cpp
	umts_sib_11_and_11_bis_container.h
	umts_sib_11_bis_container.cpp
	umts_sib_11_bis_container.h
	umts_sib_11_container.cpp
	umts_sib_11_container.h
	umts_sib_18_container.cpp
	umts_sib_18_container.h
	umts_system_information_container.cpp
	umts_system_information_container.h	
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/asn1_config.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/asn1_types.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/bit_stream_container.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/decode_support_functions.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/pdu_element.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/pdu_element.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/per_decoder_container.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/per_decoder_container.h
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/per_decoder_interface.cpp
	${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/layer_3_decoder_common/per_decoder_interface.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)

include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/umts_rrc_asn_library")
include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/umts_layer_3_decoder")

add_definitions (/DBUILDING_DLL)

add_library (umts_layer_3_decoder SHARED ${umts_layer_3_decoder_SRCS})

target_link_libraries (umts_layer_3_decoder common)
target_link_libraries (umts_layer_3_decoder layer_3_common)
target_link_libraries (umts_layer_3_decoder umts_rrc_asn_library)
