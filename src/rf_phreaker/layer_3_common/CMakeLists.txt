cmake_minimum_required (VERSION 2.8)

project (layer_3_common)

# layer_3_common version number.
# TODO - finish this when you have time!
set (layer_3_common_VERSION_MAJOR 1)
set (layer_3_common_VERSION_MINOR 0)
set (layer_3_common_VERSION_PATCH 0)
set (layer_3_common_VERSION_TWEAK 0)

# Set the source files.
set (layer_3_common_SRCS 
	bcch_bch_message_aggregate.cpp
	bcch_bch_message_aggregate.h
	gsm_layer_3_message_aggregate.cpp
	gsm_layer_3_message_aggregate.h
	lte_rrc_message_aggregate.cpp
	lte_rrc_message_aggregate.h
	pdu_element_types.h
	uint16_string.cpp
	uint16_string.h
	umts_bcch_bch_message_aggregate.cpp
	umts_bcch_bch_message_aggregate.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)
		
add_library (layer_3_common STATIC ${layer_3_common_SRCS})