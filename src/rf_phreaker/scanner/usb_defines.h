#pragma once

#ifdef _WINDOWS
#include <windows.h>
#endif

typedef PVOID USB_HANDLE;
typedef ULONG USB_STATUS;

namespace rf_phreaker { namespace scanner {


static const int ftdi_port_opened = 0x1;
static const int ftdi_high_speed = 0x2;

//
// Device status
//
enum usb_status { 
	USB_OK,
	USB_INVALID_HANDLE,
	USB_DEVICE_NOT_FOUND,
	USB_DEVICE_NOT_OPENED,
	USB_IO_ERROR,
	USB_INSUFFICIENT_RESOURCES,
	USB_INVALID_PARAMETER,
	USB_INVALID_BAUD_RATE,

	USB_DEVICE_NOT_OPENED_FOR_ERASE,
	USB_DEVICE_NOT_OPENED_FOR_WRITE,
	USB_FAILED_TO_WRITE_DEVICE,
	USB_EEPROM_READ_FAILED,
	USB_EEPROM_WRITE_FAILED,
	USB_EEPROM_ERASE_FAILED,
	USB_EEPROM_NOT_PRESENT,
	USB_EEPROM_NOT_PROGRAMMED,
	USB_INVALID_ARGS,
	USB_NOT_SUPPORTED,
	USB_OTHER_ERROR,
	USB_DEVICE_LIST_NOT_READY,
};

}}