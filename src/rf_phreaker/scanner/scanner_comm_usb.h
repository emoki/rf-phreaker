#pragma once

#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/comm_usb_info.h"
#include "rf_phreaker/scanner/usb_interface.h"
#include "rf_phreaker/scanner/usb_defines.h"

#include <map>
#include <memory>

namespace rf_phreaker { namespace scanner {

// Synchronous data transfer should be handled using the write_and_read functions or transfer_packet.

class scanner_comm_usb : public scanner_comm
{
public:
	scanner_comm_usb(comm_type type = USB_FTDI_DEVICE, const std::string &synchronous_indicator = "go;\r");

	virtual ~scanner_comm_usb(void);

	std::vector<comm_info_ptr> list_scanners();

	bool open_scanner(const scanner_id_type &id);

	bool close_scanner();

	void transfer_packet(packet &p);

	void transfer_packet_container(packet_container &send_receive_container);

	void transfer_packet_container(packet_container &send_container, char *read_buf);

	void write(const char *write_buf, size_t bytes_to_write);

	void read(char *read_buf, size_t bytes_to_read);
	
	void reset();

	bool is_scanner_open() const;

	std::string connected_scanner_description() const;

	scanner_id_type connected_scanner_id() const;

protected:
	comm_usb_info_ptr find_scanner(scanner_id_type id) const;

	void switch_to_synchronous_if_necessary(const char *write_buf, size_t bytes_to_write);

	void reset_synchronous_if_necessary();

	void resize_read_buffer(size_t bytes);

	std::unique_ptr<usb_interface> usb_interface_;

	comm_usb_info_ptr connected_comm_;

	buf_type write_buffer_;

	buf_type read_buffer_;

	const std::string synchronous_indicator_;

	static const size_t buffer_size_ = 1024 * 10;

	bool synchronous_fifo_mode_;

	std::string scanner_description_;
};

}}