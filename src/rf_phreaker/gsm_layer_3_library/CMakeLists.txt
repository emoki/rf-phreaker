

project (gsm_layer_3_library)

# gsm_layer_3_library version number.
# TODO - finish this when you have time!
set (gsm_layer_3_library_VERSION_MAJOR 1)
set (gsm_layer_3_library_VERSION_MINOR 0)
set (gsm_layer_3_library_VERSION_PATCH 0)
set (gsm_layer_3_library_VERSION_TWEAK 0)

# Set the source files.
set (gsm_layer_3_library_SRCS
	CSN1DataTypes_RR.c
	CSN1DataTypes_RR.h
	ed_c_known_ie_RR.c
	ed_c_known_ie_RR.h
	ed_c_recog_RR.c
	ed_c_recog_RR.h
	ed_c_RR.c
	ed_c_RR.h
	endec_configs_RR.h
	RRDownlink_RR.c
	RRDownlink_RR.h
	RRPLENDownlink_RR.c
	RRPLENDownlink_RR.h
	RRShortPD_RR.c	
	RRShortPD_RR.h
	RRUplink_RR.c
	RRUplink_RR.h
	UserDefinedDataTypes_RR.c
	UserDefinedDataTypes_RR.h
	bitencode.c
	bitencode.h
	csn1clib.c
	csn1clib.h
	csn1lib.c
	csn1lib.h
	ed_access.cpp
	ed_access.h
	ed_access_class.h
	ed_access_data.h
	ed_access_util.h
	ed_c_dump_RR.c
	ed_c_dump_RR.h
	ed_data.h
	ed_dump.c
	ed_dump.h
	ed_dump_file.c
	ed_dump_file.h
	ed_dump_val.c
	ed_dump_val.h
	ed_dynamic.c
	ed_dynamic.h
	ed_lib.c
	ed_lib.h
#	ed_lib_sdl.c
#	ed_lib_sdl.h
	ed_tlv.h
	ed_user.h
	ts44.018_support.c
	ts44.018_support.h
	gsm_bit_stream.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (gsm_layer_3_library STATIC ${gsm_layer_3_library_SRCS})

