project (protobuf_specific_tests)

# protobuf_specific_tests version number.
# TODO - finish this when you have time!
set (protobuf_specific_tests_VERSION_MAJOR 1)
set (protobuf_specific_tests_VERSION_MINOR 0)
set (protobuf_specific_tests_VERSION_PATCH 0)
set (protobuf_specific_tests_VERSION_TWEAK 0)

# Set the source files.
set (protobuf_specific_tests_SRCS
	io_gtests.cpp
	meas_manager.h 
	protobuf_specific_gtests.cpp
	protobuf_specific_tests.cpp
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_executable (protobuf_specific_tests  ${protobuf_specific_tests_SRCS})

target_link_libraries (protobuf_specific_tests protobuf_specific)
target_link_libraries (protobuf_specific_tests layer_3_common)
target_link_libraries (protobuf_specific_tests gmock)
target_link_libraries (protobuf_specific_tests Qt5::Core)