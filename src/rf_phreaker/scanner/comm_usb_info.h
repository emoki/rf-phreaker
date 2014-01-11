#pragma once

#include "rf_phreaker/scanner/comm_info.h"
#include "rf_phreaker/scanner/usb_defines.h"
#include <memory>

namespace rf_phreaker { namespace scanner {

class comm_usb_info;
typedef std::shared_ptr<comm_usb_info> comm_usb_info_ptr;

class comm_usb_info : public comm_info
{
public:
	//comm_usb_info(/*scanner_id_type id, const std::string &description, bool is_open*/)
	//	: comm_info(/*id, description, is_open*/)
	//{}

	//virtual comm_usb_info& operator =(comm_usb_info other) = 0;

    virtual std::string serial() const = 0;
        
	virtual bool port_opened() const = 0;
    
	virtual bool high_speed() const = 0;
    
	virtual bool full_speed() const = 0;
    
	virtual USB_HANDLE usb_handle() const = 0;

	virtual int location() const = 0;

    virtual void set_usb_handle(USB_HANDLE handle) = 0;

	virtual void clear() = 0;
};

}}