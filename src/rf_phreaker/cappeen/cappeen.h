#ifndef __CAPPEEN_API_H__
#define __CAPPEEN_API_H__

#ifdef BUILDING_DLL
#define CAPPEEN_API __declspec(dllexport)
#else
#define CAPPEEN_API __declspec(dllimport)
#endif


#include "beagle_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup beagle beagle_dll
@{
*/
/**
@mainpage
Cappeen API is a 32-bit compiled Microsoft Visual Studio C++ DLL that allows users to remotely control the cappeen unit and access its signal measurements.  
Communication occurs via API functions and callback mechanisms and uses plain old data structures to pass information.\n\n Once connection to a cappeen unit 
has been established, GPS information is outputted continuously.  Scanner information is outputted when a change to the beagle state has occurred.  For 
instance, when opening and closing the unit or starting and stopping the collection.\n\n At the start of collection the user specifies specific bands to 
sweep.  During collection all valid cells are outputted continuously.  Any layer 3 information is outputted when it is decoded.  Output ceases when 
user stops collection.  The user cannot adjust specified bands during collection.\n\n Errors are communicated via API return values and the 
cappeen_delegate::available_error callback mechanism.
*/
	
/**
@param del Used for callback functionality.    
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.

@remarks Only needs to be called once.
*/
CAPPEEN_API long cappeen_initialize(beagle_api::beagle_delegate *del);

/**
Closes connection to any units, ensures all threads have stopped, deletes main class.
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.

@remarks Should be called before exiting app.
*/
CAPPEEN_API long cappeen_clean_up();

/**
Retrieves a character string which lists the serial numbers for all units connected but not opened.
	If there is more than one unit connected, the serial"substrings" are separated by a semicolon (';').
@param list [out] Contains the list of connected units HWID list.
@param buf_size Size (in bytes) of the buffer for list.  Should be at least 1024.
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
*/
CAPPEEN_API long cappeen_list_available_units(char *list, unsigned int buf_size);

/**
Opens a communications channel to a specific unit.  This also starts GPS collection.
	Prior to starting collection the unit must be "opened" using this function.
@param serial Contains the serial number (Hardware ID) of the unit to open.
@param buf_size Size (in bytes) of the buffer for serial.  
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
@remarks
Only one unit can be opened at any given time.  
*/
CAPPEEN_API long cappeen_open_unit(const char *serial, unsigned int buf_size);

/**
Closes the communication channel to a specific unit.  
@param serial Contains the serial number of the unit to close.
@param buf_size Size (in bytes) of the buffer for serial.  
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
*/
CAPPEEN_API long cappeen_close_unit(const char *serial, unsigned int buf_size);

/**
Stops data collection.
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
	
@remarks
Stops collection threads.  
*/
CAPPEEN_API long cappeen_stop_collection();

/**
Starts data collection.
@param collection Contains various data pertinent to collecting.
@return
Returns status in form of a long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
*/
CAPPEEN_API long cappeen_start_collection(const beagle_api::collection_info &collection, bool perform_quick_scan);

/**
Starts the frequency correction process.  
@remarks
The WCDMA bands specified will be scanned for valid WCDMA cells.  Using the WCDMA cells found, the API will adjust
VCTCXO trim to minimize any frequency error within the hardware.  If successful the API will output an updated beagle_info with the new correction value
and date.  If unable to find valid UMTS cells after sweeping the bands, correction frequency process fails and is signified by the output of the error,
FREQUENCY_CORRECTION_FAILED.

Due to time considerations, when sweeping a band we cannot account for large frequency errors.  If frequency correction fails after sweeping the band(s), if possible try 
a lower band, where the frequency error has a lesser effect, or specify the actual WCDMA frequencies for frequency correction.
*/
CAPPEEN_API long cappeen_start_frequency_correction_using_sweep(const beagle_api::collection_info &collection);

/**
Starts the frequency correction process.  
@remarks
Using the WCDMA channels specified, the API will adjust VCTCXO trim to minimize any frequency error within the hardware.  
If successful the API will output an updated beagle_info with the new correction value and date.  If unable to find valid UMTS cells in the frequencies specified 
the frequency process fails and is signified by the output of the error, FREQUENCY_CORRECTION_FAILED. 

Because we are most likely only dwelling on several frequencies, we can account for a larger frequency error and are more likely to see weaker cells.
*/
CAPPEEN_API long cappeen_start_frequency_correction_using_frequencies(uint32_t *wcdma_frequencies, int num_channels);

/**
Inputs new license.
@param serial Specifies which unit will have it's license updated.
@param serial_buf_size Size (in bytes) of the serial.  
@param new_license_filename Specifies the license filename to be used when updating the unit.
@param license_buf_size Size (in bytes) of the new_license_filename.
@return
Returns status in form of long\n
0 if operation completed successfully\n
For further info please see ERRORCODES.
@remarks
Communication should have already been established with the unit via open_unit.
*/
CAPPEEN_API long cappeen_input_new_license(const char *serial, uint32_t serial_buf_size, const char *new_license_filename, uint32_t license_buf_size);

/** 
@return
Returns the version number.
*/
CAPPEEN_API const char* cappeen_api_version();


/**
@}
*/


#ifdef __cplusplus
} // end extern C
#endif



#endif