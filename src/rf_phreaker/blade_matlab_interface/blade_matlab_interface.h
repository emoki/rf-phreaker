#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#endif
#else
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllimport))
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif
#endif
#define DLL_LOCAL
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define DLL_PUBLIC
#define DLL_LOCAL
#endif
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


	int DLL_PUBLIC num_blade_devices_connected(int *num_devices);

	/*
		Blade devices delimited using ";".  Last terminated with ";;".
		Each blade device serial is 33 characters long.
		Return value of -999 represents list_size is not large enough to contain entire device_list.
	*/
	int DLL_PUBLIC list_blade_devices(char *device_list, int list_size);

	int DLL_PUBLIC open_blade_device(const char *serial);

	int DLL_PUBLIC open_first_blade_device();

	int DLL_PUBLIC close_blade_device();

	/*
		usb_speed valid values: 2 (usb 2.0), 3 (usb 3.0)
		TODO - Add version numbers.
	*/
	int DLL_PUBLIC get_connected_device_info(char *serial, int serial_size, int *usb_speed);

	/* 
		lna_gain valid values: 1 -> LNA_BYPASS, 2 -> LNA_MID, 3 -> LNA_MAX
		rx_gain_vga1 valid values: 5 <-> 30
		rx_gain_vga2 values: 0 <-> 30
	*/
	int DLL_PUBLIC get_rf_data(int64_t frequency_hz, int bandwidth_hz, int64_t sampling_rate_hz, int lna_gain, int rx_gain_vga1, int rx_gain_vga2, float *iq_data, int num_samples);

	/*
		This value may not be saved between power cycles?
	*/
	int DLL_PUBLIC set_vctcxo_trim(uint16_t trim);

	/*
		This may be constant, i.e. it always returns the value written to the EEPROM during calibration?
	*/
	int DLL_PUBLIC read_vctcxo_trim(uint16_t *trim);

	/*
		Read a configuration GPIO register
	*/
	int DLL_PUBLIC read_gpio(uint32_t *value);

	/*
		Write a configuration GPIO register. Callers should be sure to perform a
		read-modify-write sequence to avoid accidentally clearing other
		GPIO bits that may be set by the library internally.
	*/
	int DLL_PUBLIC set_gpio(uint32_t value);

	/* 
		Return value of -999 represents description_size is not large enough to contain entire error message.
	*/
	int DLL_PUBLIC get_last_error(char* description, int description_size);


#ifdef __cplusplus
}
#endif