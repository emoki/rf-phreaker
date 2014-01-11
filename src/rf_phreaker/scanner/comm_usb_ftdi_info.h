#ifndef USB_INFO_H
#define USB_INFO_H

#include "ftd2xx.h"

#include "rf_phreaker/scanner/scanner_types.h"
#include "rf_phreaker/scanner/comm_usb_info.h"
#include "rf_phreaker/scanner/usb_defines.h"

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

namespace rf_phreaker { namespace scanner {

class comm_usb_ftdi_info : public comm_usb_info
{
public:
    comm_usb_ftdi_info();

    comm_usb_ftdi_info(FT_DEVICE_LIST_INFO_NODE node);

	comm_usb_ftdi_info(const comm_usb_ftdi_info &other)
	{
		memcpy(&node_, &other.node_, sizeof(node_));
	}

	comm_usb_ftdi_info(comm_usb_ftdi_info &&other)
	{
		std::swap(node_, other.node_);
	}

	comm_usb_ftdi_info& operator =(comm_usb_ftdi_info other)
	{
		std::swap(other.node_, node_);
		return *this;
	};

	comm_type type() const { return USB_FTDI_DEVICE; }

	scanner_id_type id() const { return /*boost::lexical_cast<scanner_id_type>(*/node_.SerialNumber/*)*/; } 

	bool is_open() const { return port_opened(); }

    std::string serial() const;
    
	std::string description() const;
    
	bool port_opened() const;
    
	bool high_speed() const;
    
	bool full_speed() const;
    
	USB_HANDLE usb_handle() const;

	int location() const;

    void set_usb_handle(USB_HANDLE handle);

	void clear();
private:
    FT_DEVICE_LIST_INFO_NODE node_;
};

}}

#endif // USB_INFO_H
