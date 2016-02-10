project (protobuf_specific)

cmake_policy (SET CMP0020 NEW)
	
# protobuf_specific version number.
# TODO - finish this when you have time!
set (protobuf_specific_VERSION_MAJOR 1)
set (protobuf_specific_VERSION_MINOR 0)
set (protobuf_specific_VERSION_PATCH 0)
set (protobuf_specific_VERSION_TWEAK 0)

# Set the source files.
set (protobuf_specific_SRCS 
	io.h
	rf_phreaker_serialization.h
	rf_phreaker.pb.h
	rf_phreaker.pb.cc
	rf_phreaker.proto
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)


add_library (protobuf_specific STATIC ${protobuf_specific_SRCS})

target_link_libraries (protobuf_specific common)
target_link_libraries (protobuf_specific libprotobuf)
