#include "rf_phreaker/scanner/scanner_comm_usb.h"
#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/usb_ftdi.h"
#include "rf_phreaker/scanner/fake_usb_ftdi.h"
#include "rf_phreaker/common/exception_types.h"

using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

scanner_comm_usb::scanner_comm_usb(comm_type type, const std::string &synchronous_indicator)
	: synchronous_indicator_(synchronous_indicator)
	, synchronous_fifo_mode_(false)
	, scanner_description_(scanner_description)
{
	switch(type)
	{
	case USB_FTDI_DEVICE:
		usb_interface_.reset(new usb_ftdi);
		connected_comm_.reset(new comm_usb_ftdi_info());
		break;
	case FAKE_USB_FTDI_DEVICE:
		usb_interface_.reset(new fake_usb_ftdi);
		connected_comm_.reset(new comm_usb_ftdi_info());
		break;
	default:
		throw misc_error("Unable to construct scanner_comm_usb.  Unknown usb type.");
	}

	write_buffer_.resize(buffer_size_);	
	read_buffer_.resize(1);	
}


scanner_comm_usb::~scanner_comm_usb(void)
{
}

std::vector<comm_info_ptr> scanner_comm_usb::list_scanners()
{
	auto usb_scanners = usb_interface_->list_devices();

	std::vector<comm_info_ptr> comm_infos;
	
	for(auto it : usb_scanners) {
		if(scanner_description_.find(it->description()) != std::string::npos)
			comm_infos.push_back(it);
	}

	return comm_infos;
}

bool scanner_comm_usb::open_scanner(const scanner_id_type &id)
{
	FT_HANDLE handle;
	usb_interface_->open_device(boost::lexical_cast<std::string>(id), handle);

	auto comm = find_scanner(id);

	if(comm->is_open())
	{		
		connected_comm_ = comm;
		usb_interface_->set_timeouts(connected_comm_->usb_handle(), 1000, 1000);
		return true;
	}
	else
	{
		connected_comm_->clear();
		return false;
	}
}

bool scanner_comm_usb::close_scanner()
{
	usb_interface_->close_device(connected_comm_->usb_handle());
	connected_comm_->clear();
	return true;
}

void scanner_comm_usb::transfer_packet(packet &p)
{
#ifdef _DEBUG
	memset(&write_buffer_[0], 0, write_buffer_.size());
	memset(&read_buffer_[0], 0, read_buffer_.size());
#endif

	const auto it = p.serialize(write_buffer_.begin());

	write(&write_buffer_[0], it - write_buffer_.begin());

	const auto return_bytes = p.return_bytes_expected(); 
	if(return_bytes)
	{
		if(read_buffer_.size() < return_bytes)
			read_buffer_.resize(return_bytes);

		switch_to_synchronous_if_necessary(&write_buffer_[0], it - write_buffer_.begin());

		read(&read_buffer_[0], return_bytes);

		reset_synchronous_if_necessary();
	}

	p.parse(read_buffer_.begin());
}

void scanner_comm_usb::resize_read_buffer(size_t)
{
}

void scanner_comm_usb::transfer_packet_container(packet_container &container)
{
#ifdef _DEBUG
	memset(&write_buffer_[0], 0, write_buffer_.size());
	memset(&read_buffer_[0], 0, read_buffer_.size());
#endif

	auto it = container.serialize(write_buffer_.begin());

	write(&write_buffer_[0], it - write_buffer_.begin());

	const auto return_bytes = container.return_bytes_expected(); 
	if(return_bytes)
	{
		if(read_buffer_.size() < return_bytes)
			read_buffer_.resize(return_bytes);

		switch_to_synchronous_if_necessary(&write_buffer_[0], it - write_buffer_.begin());

		read(&read_buffer_[0], return_bytes);

		reset_synchronous_if_necessary();
	}

	container.parse(read_buffer_.begin());
}

void scanner_comm_usb::transfer_packet_container(packet_container &container, char *read_buf)
{
	const auto return_bytes = container.return_bytes_expected(); 

#ifdef _DEBUG
	memset(&write_buffer_[0], 0, write_buffer_.size());
	memset(&read_buf[0], 0, return_bytes);
#endif

	auto it = container.serialize(write_buffer_.begin());

	write(&write_buffer_[0], it - write_buffer_.begin());

	if(return_bytes)
	{
		Sleep(20);
		switch_to_synchronous_if_necessary(&write_buffer_[0], it - write_buffer_.begin());

		read(read_buf, return_bytes);

		reset_synchronous_if_necessary();
	}

	container.parse(read_buf);
}

void scanner_comm_usb::write(const char *write_buf, size_t bytes_to_write)
{
	size_t bytes_written = 0;

	for(size_t write_pos = 0; write_pos < bytes_to_write; write_pos += serialize_buffer_size)
	{	
		// Pause and let the microcontroller work.
		//if(write_pos != 0) Sleep(1000);

		size_t tmp_written = 0;
		size_t tmp_bytes_to_write = (bytes_to_write - write_pos < serialize_buffer_size) ? bytes_to_write - write_pos : serialize_buffer_size;
		usb_interface_->write(connected_comm_->usb_handle(), &const_cast<char*>(write_buf)[write_pos], tmp_bytes_to_write, tmp_written);
		bytes_written += tmp_written;
	}

	if(bytes_written != bytes_to_write)
		throw comm_error("We did not write enough bytes when writing to USB comm.  Most likely a timeout.");
}

void scanner_comm_usb::read(char *read_buf, size_t bytes_to_read)
{
	size_t bytes_read = 0;

	usb_interface_->read(connected_comm_->usb_handle(), &read_buf[0], bytes_to_read, bytes_read);

	if(bytes_read != bytes_to_read)
		throw comm_error("We did not read enough bytes when reading from USB comm.");
}

//void scanner_comm_usb::write_and_read(const buf_type &write_buf, buf_type &read_buf, size_t bytes_to_write, size_t bytes_to_read)
//{
//	write(write_buf, bytes_to_write);
//
//	read(read_buf, bytes_to_read);
//
//	//size_t bytes_written = 0;
//	//size_t bytes_read = 0;
//
//	//for(size_t write_pos = 0; write_pos < write_buf.size(); write_pos += serialize_buffer_size)
//	//{	
//	//	size_t tmp_written = 0;
//
//	//	size_t bytes_to_write = (write_buf.size() - bytes_written < serialize_buffer_size) ? write_buf.size() - bytes_written : serialize_buffer_size;
//	//	
//	//	while(write_buf[bytes_written + bytes_to_write - 1] != '\r')
//	//		--bytes_to_write;
//	//	
//	//	//++bytes_to_write;
//
//	//	usb_interface_->write(connected_comm_.ft_handle(), &const_cast<buf_type&>(write_buf)[bytes_written], bytes_to_write, tmp_written);
//	//	
//	//	bytes_written += tmp_written;
//
//	//	Sleep(100);
//
//	//	size_t tmp_read = 0;
//	//	usb_interface_->read(connected_comm_.ft_handle(), &read_buf[bytes_read], read_buf.size() - bytes_read, tmp_read);
//
//	//	bytes_read += tmp_read;
//
//	//	if(bytes_read >= read_buf.size())
//	//		break;
//	//	Sleep(100);
//	//}
//
//	//if(bytes_written != write_buf.size())
//	//	throw comm_error("We did not write enough bytes when writing to USB comm.  Most likely a timeout.");
//	//
//	//if(bytes_read != read_buf.size())
//	//	throw comm_error("We did not read enough bytes when reading from USB comm.  Most likely a timeout.");
//}

void scanner_comm_usb::switch_to_synchronous_if_necessary(const char *write_buf, size_t bytes_to_write)
{
	auto it = std::search(write_buf, write_buf + bytes_to_write, synchronous_indicator_.begin(), synchronous_indicator_.end());

	if(it != write_buf + bytes_to_write)
	{
		usb_interface_->set_receive_synchronous_fifo_mode(connected_comm_->usb_handle());
		synchronous_fifo_mode_ = true;
	}
}

void scanner_comm_usb::reset_synchronous_if_necessary()
{
	// ftdi FT_GetBitMode does not work correctly or I'm using it wrong so I've just use member
	if(synchronous_fifo_mode_)
	{
		usb_interface_->reset_fifo_mode(connected_comm_->usb_handle());
		synchronous_fifo_mode_ = false;
	}
}

void scanner_comm_usb::reset()
{
	// Only available on windows.  Wait to implement.
}

bool scanner_comm_usb::is_scanner_open() const
{
	auto it = find_scanner(connected_comm_->id());
	
	return it ? it->is_open() : false;
}

comm_usb_info_ptr scanner_comm_usb::find_scanner(scanner_id_type id) const
{
	auto usb_scanners = usb_interface_->list_devices();
	
	auto it = std::find_if(usb_scanners.begin(), usb_scanners.end(), [&](const comm_usb_info_ptr &info)
	{
		return info->id() == id;
	});

	return it != usb_scanners.end() ? *it : nullptr;
}

std::string scanner_comm_usb::connected_scanner_description() const
{
	return connected_comm_->description();
}

scanner_id_type scanner_comm_usb::connected_scanner_id() const
{
	return connected_comm_->id();
}

