cmake_minimum_required (VERSION 2.8)

project (gsm_layer_3_decoder)

# gsm_layer_3_decoder version number.
# TODO - finish this when you have time!
set (gsm_layer_3_decoder_VERSION_MAJOR 1)
set (gsm_layer_3_decoder_VERSION_MINOR 0)
set (gsm_layer_3_decoder_VERSION_PATCH 0)
set (gsm_layer_3_decoder_VERSION_TWEAK 0)

# Set the source files.
set (gsm_layer_3_decoder_SRCS 
	gsm_layer_3_container.cpp
	gsm_layer_3_container.h
	gsm_layer_3_decoder.cpp
	gsm_layer_3_decoder.h
	populate_data_interface.h
	si_2_container.cpp
	si_2_container.h
	si_2bis_container.cpp
	si_2bis_container.h
	si_2quarter_container.cpp
	si_2quarter_container.h
	si_2ter_container.cpp
	si_2ter_container.h
	si_3_container.cpp
	si_3_container.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)


add_library (gsm_layer_3_decoder SHARED ${gsm_layer_3_decoder_SRCS})

target_link_libraries (gsm_layer_3_decoder common)
target_link_libraries (gsm_layer_3_decoder gsm_layer_3_library)
