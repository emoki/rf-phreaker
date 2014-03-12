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
The cappeen api is a multithreaded C++ software layer that handles the collection of WCDMA and LTE data allowing the client 
to view data collection from a high level. It interfaces with the client application through synchronous function calls 
and callback routines (see beagle_delegate). 
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
Closes connection to any units, ensures all threads have stopped, deletes main class, main events, timers, and semaphores.
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
@param buf_size Size (in bytes) of the buffer for serial.  Should be at least 1024.
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
@param buf_size Size (in bytes) of the buffer for serial.  Should be at least 1024.
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
@remarks
Before starting collection BEAGLESTATE should be BEAGLE_READY.  Collecting with a state of BEAGLE_WARMINGUP will result inaccurate data.
*/
CAPPEEN_API long cappeen_start_collection(const beagle_api::collection_info &collection);

/**
Inputs new license.
@param serial Specifies which unit will have it's license updated.
@param buf_size Size (in bytes) of the serial.  Should be at least 1024.
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