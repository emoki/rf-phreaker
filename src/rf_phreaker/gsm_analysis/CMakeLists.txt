

project (gsm_analysis)

# gsm_analysis version number.
# TODO - finish this when you have time!
set (gsm_analysis_VERSION_MAJOR 1)
set (gsm_analysis_VERSION_MINOR 0)
set (gsm_analysis_VERSION_PATCH 0)
set (gsm_analysis_VERSION_TWEAK 0)

# Set the source files.
set (gsm_analysis_SRCS 
	gsm_analysis_data.h
	gsm_analysis_interface.cpp
	gsm_analysis_interface.h
	gsm_convolutional_decoder.cpp
	gsm_convolutional_decoder.h
	gsm_types.h
	gsm_defs.h
	gsm_config.h
	gsm_analysis.cpp
	gsm_analysis.h
	gsm_analysis_impl.h
	gsm_measurement.h
	gsm_measurement_io.h
	gsm_sync_templates.h
	modulated_signal_correlator.cpp
	modulated_signal_correlator.h
	netstart.cpp
	netstart.h
	ns_bsic.cpp
	ns_bsic.h
	ns_cgi.cpp
	ns_cgi.h
	ns_fcch.cpp
	ns_fcch.h
	ns_row.cpp
	ns_row.h
	ns_sp.cpp
	ns_sp.h
	ns_sync.cpp
	ns_sync.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp
	${SRC_PLATFORM_SPECIFIC}/dllmain.cpp)


add_definitions (/DBUILDING_DLL)

add_library (gsm_analysis SHARED ${gsm_analysis_SRCS})

target_link_libraries (gsm_analysis common)
target_link_libraries (gsm_analysis fir_filter)
target_link_libraries (gsm_analysis layer_3_common)

