#pragma once

#include <vector>

#include "rf_phreaker/scanner/comm_usb_info.h"
#include "rf_phreaker/scanner/usb_defines.h"

namespace rf_phreaker { namespace scanner {

class usb_interface
{
public:
    virtual std::vector<comm_usb_info_ptr> list_devices() = 0;

    virtual void open_device(int location, USB_HANDLE &handle) = 0;

	virtual void open_device(const std::string &serial, USB_HANDLE &handle) = 0;

    virtual void close_device(USB_HANDLE handle) = 0;

    virtual void write(USB_HANDLE handle, char *buf, size_t bytes_to_write, size_t &bytes_written) = 0;

    virtual void read(USB_HANDLE handle, char *buf, size_t bytes_to_read, size_t &bytes_read) = 0;

    virtual void set_receive_synchronous_fifo_mode(USB_HANDLE handle) = 0;

    virtual void reset_fifo_mode(USB_HANDLE handle) = 0;

    virtual bool is_synchronous_fifo_mode(USB_HANDLE handle) = 0;

 	virtual void set_timeouts(USB_HANDLE handle, int read_timeout, int write_timeout) = 0;

    virtual USB_STATUS log_error_if_any(USB_STATUS status, const char *description = "") = 0;

    virtual std::string convert_status(USB_STATUS status) = 0;

	virtual void handle_error(const std::string &serial, USB_HANDLE &handle) = 0;

	//virtual void wait_for_data() = 0;
};

}}