

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
	common_utility.cpp
	common_utility.h
	concurrent.h
	config_file.cpp
	config_file.h
	cross_correlation_incoherent_and_coherent_addition.cpp
	cross_correlation_incoherent_and_coherent_addition.h
	delegate_sink.h
	delegate_sink_tmp.h
	delegate_sink_tmp.cpp
	exception_types.h
	fft_helper.cpp
	fft_helper.h
	frequency_shifter.h
	frequency_bin_calculator.h
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
	serialization_helper.h
	signal_slot.h
	singleton.h
	sort_peaks.h
	stats_tracker.h
	${SRC_PLATFORM_SPECIFIC}/stdafx.cpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library (common SHARED ${common_SRCS}) 
target_link_libraries (common ${TBB_LIBRARY})
target_link_libraries (common ipp_custom)
target_link_libraries (common g3logger_shared)
target_link_libraries (common hash_utility)

# For some reason, cmake wasn't adding boost libraries to this project
# so we're adding them manually.  Revist later after upgrading cmake.
target_link_libraries (common ${Boost_LIBRARIES}) 