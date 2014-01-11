#include "rf_phreaker/scanner/comm_usb_ftdi_info.h"

using namespace rf_phreaker::scanner;

comm_usb_ftdi_info::comm_usb_ftdi_info()
{
    memset(&node_, 0, sizeof(node_));
}

comm_usb_ftdi_info::comm_usb_ftdi_info(FT_DEVICE_LIST_INFO_NODE node)
	: node_(node)
{
}

std::string comm_usb_ftdi_info::serial() const
{
    return std::string(node_.SerialNumber);
}

std::string comm_usb_ftdi_info::description() const
{
    return std::string(node_.Description);
}

bool comm_usb_ftdi_info::port_opened() const
{
    return node_.Flags & ftdi_port_opened;
}

bool comm_usb_ftdi_info::high_speed() const
{
    return (node_.Flags & ftdi_high_speed) == ftdi_high_speed ? true : false;
}

bool comm_usb_ftdi_info::full_speed() const
{
    return (node_.Flags & ftdi_high_speed) != ftdi_high_speed ? true : false;
}

USB_HANDLE comm_usb_ftdi_info::usb_handle() const
{
    return node_.ftHandle;
}

int comm_usb_ftdi_info::location() const
{
    return node_.LocId;
}

void comm_usb_ftdi_info::set_usb_handle(USB_HANDLE handle)
{
    node_.ftHandle = handle;
}

void comm_usb_ftdi_info::clear()
{
	node_.Flags = 0;
	node_.Type = 0;
	node_.ID = 0;
	node_.LocId = 0;
	node_.SerialNumber[0] = 0;
	node_.Description[0] = 0;
	node_.ftHandle = 0;
}