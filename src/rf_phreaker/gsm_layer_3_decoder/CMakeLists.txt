

project (gsm_layer_3_decoder)

# gsm_layer_3_decoder version number.
# TODO - finish this when you have time!
set (gsm_layer_3_decoder_VERSION_MAJOR 1)
set (gsm_layer_3_decoder_VERSION_MINOR 0)
set (gsm_layer_3_decoder_VERSION_PATCH 0)
set (gsm_layer_3_decoder_VERSION_TWEAK 0)

# Set the source files.
set (gsm_layer_3_decoder_SRCS 
	gsm_layer_3_decoder.cpp
	gsm_layer_3_decoder.h
	gsm_layer_3_utility.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (gsm_layer_3_decoder SHARED ${gsm_layer_3_decoder_SRCS})

target_link_libraries (gsm_layer_3_decoder common)
target_link_libraries (gsm_layer_3_decoder layer_3_common)
target_link_libraries (gsm_layer_3_decoder gsm_layer_3_library)
target_link_libraries (gsm_layer_3_decoder qt_specific)
