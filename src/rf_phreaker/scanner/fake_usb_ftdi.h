#pragma once

#include "rf_phreaker/scanner/usb_interface.h"
#include "rf_phreaker/scanner/usb_ftdi.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/packet_helper.h"
#include "rf_phreaker/scanner/scanner_utility.h"

namespace rf_phreaker { namespace scanner {

class fake_usb_ftdi : public usb_ftdi
{
public:

	fake_usb_ftdi(void)
		: possible_handle_((FT_HANDLE)0x12345)
		, vtune_lower_(0)
		, vtune_higher_(6)
		, return_samples_(false)
		, num_samples_to_return_(0)
	{
	}

	virtual ~fake_usb_ftdi(void)
	{
	}

    std::vector<comm_usb_info_ptr> list_devices()
	{
		std::vector<comm_usb_info_ptr> usbs;
		FT_DEVICE_LIST_INFO_NODE node;
		//memset(&node.SerialNumber, 0, sizeof(node.SerialNumber));
		memcpy(&node.SerialNumber, "fake_ftdi_device", sizeof("fake_ftdi_device"));
		node.Flags = ftdi_high_speed | ftdi_port_opened; // high speed and open - used when querying devices.
		node.ftHandle = possible_handle_;
		usbs.push_back(comm_usb_info_ptr(new comm_usb_ftdi_info(node)));
		return usbs;
	}

	comm_type type() const 
	{ 
		return FAKE_USB_FTDI_DEVICE; 
	}

	void open_device(int, USB_HANDLE &handle) 
	{
		handle = possible_handle_;
		is_open_ = true;
	}

	void open_device(const std::string &, USB_HANDLE &handle)
	{
		handle = possible_handle_;
		is_open_ = true;
	}

    void close_device(USB_HANDLE handle)
	{
		if(possible_handle_ == handle)
			is_open_ = false;
	}

    void write(USB_HANDLE handle, char *buf, size_t bytes_to_write, size_t &bytes_written)
	{
		verify_usb_handle(handle);

		std::string tmp(buf, bytes_to_write);

		std::string str = remainder_of_last_write_ + tmp;

		// If the last command was cut off, store it and process it next time around.
		auto i = str.rfind(packet_terminator) + strlen(packet_terminator);
		if(i != str.size())
		{
			remainder_of_last_write_ = str.substr(i);
			str.erase(i);
		}
		else 
			remainder_of_last_write_.resize(0);

		std::string::size_type pos = 0;
		auto next_pos = pos;

		while(pos != str.size())
		{
			next_pos = str.find(packet_terminator, pos);

			auto substr = str.substr(pos, next_pos - pos);

			pos =  next_pos + strlen(packet_terminator);

			switch(packet_utility::convert_header_name(substr))
			{
				case lime_read:
				{
					lms_register_type reg = (lms_register_type)packet_utility::parse_for_specifier<2>(substr, read_specifier); 

					if(reg == lms::vtune_comparator_register)
					{
						return_bytes_group_.push_back(hex_conversion::convert_hex<2>(vtune_return_value_));
					}
					else
					{
						auto it = lms_register_writes_.find(reg);

						int return_value = 0;
						if(it != lms_register_writes_.end())
							return_value = it->second;
			
						return_bytes_group_.push_back(hex_conversion::convert_hex<2>(return_value));
					}
				}
					break;
				case lime_write:
				{
					lms_register_type reg = (lms_register_type)packet_utility::parse_for_specifier<2>(substr, write_specifier); 
					lms_value_type value = (lms_value_type)packet_utility::parse_for_specifier<2>(substr, value_specifier);

					if(reg == lms::vcocap_program_register)
					{
						set_vtune_value(value);
					}
					// We have restarted the vtune algorithm.
					else if(reg == lms::vtune_comparator_power_up_register && (lms::is_vco_comparator_power_enabled(value)))
					{
						reset_vtune();
					}
					else
						lms_register_writes_.insert(std::make_pair(reg, value));
				}
					break;
				case go:
					return_samples_ = true;
					break;
				case set_sample_size:
					num_samples_to_return_ = packet_utility::parse_for_specifier<6>(substr, value_specifier) * 4;
					break;
				case accelerator_read:
					break;
				case accelerometer_write:
					break;
				case calibrate_dds:
					break;
				case read_1pps_clock:
					break;
				case dds_reset:
					break;
				case dds_read:
					break;
				case dds_update:
					break;
				case dds_write:
					break;
				case set_decimation:
					break;
				case eeprom_read:
					break;
				case eeprom_write:
					break;
				case fpga_reset:
					break;
				case gps_off:
					break;
				case gps_on:
					break;
				case gps_reset:
					break;
				case gps_read:
					break;
				case gps_send_ascii:
					break;
				case lime_reset:
					break;
				case reset_all:
					break;
				case fpga_status:
					break;
				case set_switch_channel_select:
					break;
				case set_switch_7_9:
					break;
				case set_switch_input_select:
					break;
				case mem_test:
					break;
				case usb_reset:
					break;
				default:
					;
			}
		}

		bytes_written = bytes_to_write;
	}

    void read(USB_HANDLE handle, char *buf, size_t bytes_to_read, size_t &bytes_read)
	{
		verify_usb_handle(handle);

		bytes_read = 0;
		
		int pos = 0;

		auto it = return_bytes_group_.begin();

		for(; it != return_bytes_group_.end(); ++it)
		{
			if(bytes_read + it->size() <= bytes_to_read)
			{
				memcpy(&buf[pos], it->c_str(), it->size());
				pos += it->size();
				bytes_read += it->size();
			}
			else
			{
				int num_to_copy = it->size() - (bytes_to_read - bytes_read);
				memcpy(&buf[pos], it->c_str(), num_to_copy);
				*it = it->substr(num_to_copy);
				break;
			}
		}

		return_bytes_group_.erase(return_bytes_group_.begin(), it);	

		// Assume that snapshot data was the last requested.  For now, just increment bytes_read.
		if(return_samples_)
			bytes_read += num_samples_to_return_;
	}

    void set_receive_synchronous_fifo_mode(USB_HANDLE handle)
	{
		verify_usb_handle(handle);
		in_sync_mode_ = true;
	}

    void reset_fifo_mode(USB_HANDLE handle)
	{
		verify_usb_handle(handle);
		in_sync_mode_ = false;
	}

    bool is_synchronous_fifo_mode(USB_HANDLE handle) 
	{ 
		verify_usb_handle(handle);
		return in_sync_mode_;
	}

 	void set_timeouts(USB_HANDLE handle, int, int)
	{
		verify_usb_handle(handle);
	}

	void handle_error(const std::string &/*serial*/, USB_HANDLE &/*handle*/)
	{}

	void verify_usb_handle(USB_HANDLE handle)
	{
		if(possible_handle_ != handle)
			log_error_if_any(FT_DEVICE_NOT_FOUND, "ftdi_fake_device_function");
	}

	void set_vtune_value(lms_value_type reg_value)
	{
		int vcocap = ((reg_value & 0xFF) & ~lms::vcocap_program_default);
	
		if(vcocap < vtune_lower_)
			vtune_return_value_ = lms::convert_vtune(lms::VTUNE_HIGH);
		else if(vcocap >= vtune_lower_ && vcocap <= vtune_higher_)
			vtune_return_value_ = lms::convert_vtune(lms::VTUNE_IN_RANGE);
		else 
			vtune_return_value_ = lms::convert_vtune(lms::VTUNE_LOW);
	}

	void reset_vtune()
	{
		if(++vtune_higher_ > lms::vcocap_max_cap)
			vtune_higher_ = lms::vcocap_max_cap;

		if(++vtune_lower_ > lms::vcocap_max_cap)
		{
			vtune_lower_ = 0;
			vtune_higher_ = 6;
		}
	}



	std::string serial_;

	bool is_open_;

	bool in_sync_mode_;

	FT_HANDLE possible_handle_;

	std::vector<std::string> return_bytes_group_;
	
	std::map<lms_register_type, lms_value_type> lms_register_writes_;

	lms_value_type vtune_lower_;
	lms_value_type vtune_higher_;
	lms_value_type vtune_return_value_;

	int num_samples_to_return_;
	bool return_samples_;

	std::string remainder_of_last_write_;
};

}}