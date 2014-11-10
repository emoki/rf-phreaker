

project (common)

# common version number.
# TODO - finish this when you have time!
set (common_VERSION_MAJOR 1)
set (common_VERSION_MINOR 0)
set (common_VERSION_PATCH 0)
set (common_VERSION_TWEAK 0)

# Set the source files.
set (common_SRCS 
	active_object.h
	benchmark.h
	channel_conversion.h
	common_serialization.h
	common_types.h
	common_utility.h
	concurrent.h
	config_file.cpp
	config_file.h
	delegate_sink.h
	delegate_sink_tmp.h
	delegate_sink_tmp.cpp
	exception_types.h
	fft_helper.cpp
	fft_helper.h
	frequency_shifter.h
	ipp_array.h
	ipp_helper.h
	license.h
	log.h
	measurements.h
	measurement_io.h
	monitor_object.h
	moving_window_calculator.cpp
	moving_window_calculator.h
	operating_band_range_specifier.h
	operating_band_range_specifier.cpp
	raw_signal.h
	settings.h
	signal_slot.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

add_library (common STATIC ${common_SRCS})
target_link_libraries (common ${TBB_LIBRARY})
target_link_libraries (common ipp_custom)
target_link_libraries (common g3logger)
