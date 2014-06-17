#pragma once

#ifdef BUILDING_DLL
#define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#else
#define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


	int DLL_PUBLIC start_logging(int log_level);

	int DLL_PUBLIC num_blade_devices_connected(int *num_devices);

	/*
		Blade devices delimited using ";".  Last terminated with ";;".
		Each blade device serial is 33 characters long.
		Return value of -999 represents list_size is not large enough to contain entire device_list.
	*/
	int DLL_PUBLIC list_blade_devices(int8_t *device_list, int list_size);

	int DLL_PUBLIC open_blade_device(const char *serial);

	int DLL_PUBLIC open_first_blade_device();

	int DLL_PUBLIC close_blade_device();

	/*
		usb_speed valid values: 2 (usb 2.0), 3 (usb 3.0)
		TODO - Add version numbers.
	*/
	int DLL_PUBLIC get_connected_device_info(int8_t *serial, int serial_size, int *usb_speed);

	/* 
		lna_gain valid values: 1 -> LNA_BYPASS, 2 -> LNA_MID, 3 -> LNA_MAX
		rx_gain_vga1 valid values: 5 <-> 30
		rx_gain_vga2 values: 0 <-> 30
	*/
	int DLL_PUBLIC get_rf_data(__int64 frequency_hz, int bandwidth_hz, __int64 sampling_rate_hz, int lna_gain, 
		int rx_gain_vga1, int rx_gain_vga2, float *iq_data, int num_samples, float *signal_level,
		unsigned int switch_setting, unsigned int switch_mask);

	/*
	Does not change any lms parameters.  Only transfers IQ data.
	*/
	int DLL_PUBLIC only_get_rf_data(float *iq_data, int num_samples, float *signal_level);

	/*
		This value may not be saved between power cycles?
	*/
	int DLL_PUBLIC set_vctcxo_trim(int trim);

	/*
		This may be constant, i.e. it always returns the value written to the EEPROM during calibration?
	*/
	int DLL_PUBLIC read_vctcxo_trim(int *trim);

	/*
	*/
	int DLL_PUBLIC write_frequency_correction_value(int trim);

	/*
		Read a configuration GPIO register
	*/
	int DLL_PUBLIC read_gpio(unsigned int *value);

	/*
		Write a configuration GPIO register. Callers should be sure to perform a
		read-modify-write sequence to avoid accidentally clearing other
		GPIO bits that may be set by the library internally.
	*/
	int DLL_PUBLIC set_gpio(unsigned int value);

	/*
	*/
	int DLL_PUBLIC set_lms_reg(int address, int value);

	/*
	*/
	int DLL_PUBLIC read_lms_reg(int address, int *value);

	/*
		NULL terminated filenames.  The operation performs a read-erase-write cycle which can take up 
		to 1 or 2 minutes.  
	*/
	int DLL_PUBLIC write_calibration(const int8_t *nuand_calibration_filename, const int8_t *rf_board_calibration_filename, 
		const int8_t *switch_setting_filename);

	/*
		Set to false when the blade device is not connected to the RF board.  
		@note Default is true.
	*/
	int DLL_PUBLIC use_rf_board_adjustment_for_signal_level(bool use_adj);

	/*
		Returns the nuand adjustment.  Determines the proper RF path using switch settings portion of the calibration.
	*/
	int DLL_PUBLIC get_nuand_adjustment(__int64 frequency_hz, float *adj);

	/*
		Returns the RF board adjustment.  Determines the proper RF path using switch settings portion of the calibration.
	*/
	int DLL_PUBLIC get_rf_board_adjustment(__int64 frequency_hz, float *adj);
	
	/*
		lna_gain is not currently used.  We assume that it is LNA_GAIN_MAX.
	*/
	int DLL_PUBLIC calculate_signal_level(__int64 frequency_hz, int lna_gain, int gain_rxvga1, int gain_rxvga2,
		float digital_voltage, float *signal_level);

	/* 
		Return value of -999 represents description_size is not large enough to contain entire error message.
	*/
	int DLL_PUBLIC get_last_error(int8_t* description, int description_size);


#ifdef __cplusplus
}
#endif
