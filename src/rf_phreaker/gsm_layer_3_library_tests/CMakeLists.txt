

project (gsm_layer_3_library_tests)

# gsm_layer_3_library_tests version number.
# TODO - finish this when you have time!
set (gsm_layer_3_library_tests_VERSION_MAJOR 1)
set (gsm_layer_3_library_tests_VERSION_MINOR 0)
set (gsm_layer_3_library_tests_VERSION_PATCH 0)
set (gsm_layer_3_library_tests_VERSION_TWEAK 0)

set (gsm_layer_3_library_tests_SRCS 
	gsm_layer_3_library_tests.cpp
	test_cell_identity.cpp
	test_cell_identity.h
	test_generic_information_element.cpp
	test_generic_information_element.h
	test_gsm_bit_stream.cpp
	test_gsm_bit_stream.h
	test_info_element.cpp
	test_info_element.h
	test_l2_pseudo_length_element.cpp
	test_l2_pseudo_length_element.h
	test_location_area_identification.cpp
	test_location_area_identification.h
	test_protocol_discriminator.cpp
	test_protocol_discriminator.h
	test_skip_indicator.cpp
	test_skip_indicator.h
	test_system_information_type_2_message.cpp
	test_system_information_type_2_message.h
	test_system_information_type_2_quarter_message.cpp
	test_system_information_type_2_quarter_message.h
	test_system_information_type_2_ter_message.cpp
	test_system_information_type_2_ter_message.h
	test_system_information_type_3_message.cpp
	test_system_information_type_3_message.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_executable (gsm_layer_3_library_tests ${gsm_layer_3_library_tests_SRCS})

target_link_libraries (gsm_layer_3_library_tests commmon)
