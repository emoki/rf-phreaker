

project (gsm_layer_3_decoder_tests)

# gsm_layer_3_decoder_tests version number.
# TODO - finish this when you have time!
set (gsm_layer_3_decoder_tests_VERSION_MAJOR 1)
set (gsm_layer_3_decoder_tests_VERSION_MINOR 0)
set (gsm_layer_3_decoder_tests_VERSION_PATCH 0)
set (gsm_layer_3_decoder_tests_VERSION_TWEAK 0)

set (gsm_layer_3_decoder_tests_SRCS 
	gsm_layer_3_decoder_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (gsm_layer_3_decoder_tests ${gsm_layer_3_decoder_tests_SRCS})

target_link_libraries (gsm_layer_3_decoder_tests common)
target_link_libraries (gsm_layer_3_decoder_tests gsm_layer_3_library)
target_link_libraries (gsm_layer_3_decoder_tests gsm_layer_3_decoder)
target_link_libraries (gsm_layer_3_decoder_tests gmock)