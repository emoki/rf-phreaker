

project (lte_layer_3_decoder)

# lte_layer_3_decoder version number.
# TODO - finish this when you have time!
set (lte_layer_3_decoder_VERSION_MAJOR 1)
set (lte_layer_3_decoder_VERSION_MINOR 0)
set (lte_layer_3_decoder_VERSION_PATCH 0)
set (lte_layer_3_decoder_VERSION_TWEAK 0)

# Set the source files.
set (lte_layer_3_decoder_SRCS 
	asn_type_descriptor.h
	asn_type_descriptor.cpp
	lte_bcch_dl_sch_message.cpp
	lte_bcch_dl_sch_message.h
	lte_layer_3_decoder.cpp
	lte_layer_3_decoder.h
	lte_sib_1_parser.cpp
	lte_sib_1_parser.h
	lte_sib_4_parser.cpp
	lte_sib_4_parser.h
	lte_sib_5_parser.cpp
	lte_sib_5_parser.h
	lte_sib_6_parser.cpp
	lte_sib_6_parser.h
	lte_sib_7_parser.cpp
	lte_sib_7_parser.h
	lte_sib_8_parser.cpp
	lte_sib_8_parser.h
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


include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/lte_rrc_asn_library")
include_directories ("${rf_phreaker_SOURCE_DIR}/src/rf_phreaker/lte_layer_3_decoder")

add_definitions (/DBUILDING_DLL)

add_library (lte_layer_3_decoder SHARED ${lte_layer_3_decoder_SRCS})

target_link_libraries (lte_layer_3_decoder common)
target_link_libraries (lte_layer_3_decoder layer_3_common)
target_link_libraries (lte_layer_3_decoder lte_rrc_asn_library)
