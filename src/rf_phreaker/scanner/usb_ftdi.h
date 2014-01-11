#ifndef USB_FTDI_H
#define USB_FTDI_H

#include "ftd2xx.h"

#include "rf_phreaker/scanner/comm_usb_ftdi_info.h"
#include "rf_phreaker/scanner/usb_interface.h"
#include "rf_phreaker/scanner/usb_defines.h"
#include "rf_phreaker/scanner/io_logger.h"

#include <vector>

namespace rf_phreaker { namespace scanner {

class usb_ftdi : public usb_interface
{
public:
	usb_ftdi();

    std::vector<comm_usb_info_ptr> list_devices();

    void open_device(int location, USB_HANDLE &handle);

	void open_device(const std::string &serial, USB_HANDLE &handle);

    void close_device(USB_HANDLE handle);

    void write(USB_HANDLE handle, char *buf, size_t bytes_to_write, size_t &bytes_written);

    void read(USB_HANDLE handle, char *buf, size_t bytes_to_read, size_t &bytes_read);

    void set_receive_synchronous_fifo_mode(USB_HANDLE handle);

    void reset_fifo_mode(USB_HANDLE handle);

    bool is_synchronous_fifo_mode(USB_HANDLE handle);

 	void set_timeouts(USB_HANDLE handle, int read_timeout, int write_timeout);

    USB_STATUS log_error_if_any(USB_STATUS status, const char *description = "");

    std::string convert_status(USB_STATUS status);

	void handle_error(const std::string &serial, USB_HANDLE &handle);

private:
	io_logger logger_;
};

}}

#endif // USB_FTDI_H

