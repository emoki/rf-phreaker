#pragma once

#include "rf_phreaker/scanner/scanner_types.h"
#include "rf_phreaker/common/exception_types.h"

#include <array>
#include <iomanip>
#include <boost/format.hpp>
#include <type_traits>

namespace rf_phreaker { namespace scanner {

static const char field_delimiter = ',';
static const char packet_terminator[] = ";\r";
static const char value_specifier[] = "value";
static const char write_specifier[] = "write";
static const char read_specifier[] = "read";

static const char* header_names[] =
{
	"accel,read",
	"accel,write",
	"calibrate",
	"count",
	"dds,reset",
	"dds,read",
	"dds,update",
	"dds,write",
	"decimate,value",
	"eeprom,read",
	"eeprom,write",
	"fpga,reset",
	"go",
	"gps,off",
	"gps,on",
	"gps,reset",
	"gps",
	"gps,asciiz",
	"lime,reset",
	"lime,read",
	"lime,write",
	"reset,all",
	"size,value",
	"stat",
	"swch,value",
	"swhilo,value",
	"swin,value",
	"test,value",
	"usb,reset"
};

enum header_lookup
{
	accelerator_read,
	accelerometer_write,
	calibrate_dds,
	read_1pps_clock,
	dds_reset,
	dds_read,
	dds_update,
	dds_write,
	set_decimation,
	eeprom_read,
	eeprom_write,
	fpga_reset,
	go,
	gps_off,
	gps_on,
	gps_reset,
	gps_read,
	gps_send_ascii,
	lime_reset,
	lime_read,
	lime_write,
	reset_all,
	set_sample_size,
	fpga_status,
	set_switch_channel_select,
	set_switch_7_9,
	set_switch_input_select,
	mem_test,
	usb_reset,
	num_of_headers
};


struct packet_utility
{
	// Searches entire string.  Assumes only one header in string.
	static header_lookup convert_header_name(const std::string &name)
	{
		for(int it = accelerator_read; it != num_of_headers; ++it)
		{
			if(name.find(header_names[it]) != std::string::npos)
				return static_cast<header_lookup>(it);
		}

		throw comm_error("Unknown packet header");
	}

	template<size_t Size>
	static int parse_for_specifier(const std::string &str, const std::string &specifier)
	{
		int i = str.find(specifier) + specifier.size() + 1; // plus 1 for field delimiter
		auto substr = str.substr(i, str.find(field_delimiter, i) - i);
		return hex_conversion::convert_hex<Size>(substr.c_str());
	}

};


template<header_lookup header, size_t num_send_params = 0>
class header_array_storage
{
public:
	static const header_lookup header_ = header;
	std::array<int, num_send_params> send_data_;  
	size_t estimated_serialize_size() const { return 100; }
};


template<header_lookup header, size_t num_params>
class header_array_buf_iterator_storage : public header_array_storage<header, num_params>
{
public:
	char* iq_sample_position_;
};


template<header_lookup header, size_t num_send_params = 0, size_t return_bytes = 0, size_t num_receive_params = 0>
class header_array_known_return_bytes_storage : public header_array_storage<header, num_send_params>
{
public:
	std::array<int, num_receive_params> receive_data_;
	static const size_t expected_return_bytes_ = return_bytes;
};


class string_return_bytes_storage
{
public:
	typedef std::string data_type;
	std::string send_data_;
	buf_type receive_data_;
	size_t expected_return_bytes_;
	size_t estimated_serialize_size() const { return send_data_.size(); }
};



template<typename Packet_Storage>
class return_bytes_known_policy
{
public:
	static size_t return_bytes_expected(const Packet_Storage &data)
	{
		data; // Sometimes not referenced.
		return data.expected_return_bytes_;
	}
};

template<typename Packet_Storage>
class return_bytes_calc_using_samples_policy
{
public:
	static size_t return_bytes_expected(const Packet_Storage &data)
	{
		return data.send_data_[0] * sizeof(iq_sample_type);
	}
};


template<typename Packet_Storage, bool second_param_six_characters = false>
class serialize_max_2_params_policy
{
public:
	static buf_type::iterator serialize(buf_type::iterator it, const Packet_Storage &data)
	{
		it = std::copy(header_names[data.header_], (header_names[data.header_] + std::strlen(header_names[data.header_])), it);
		
		if(data.send_data_.size() > 0)
		{ 
			*it++ = field_delimiter;
			it = format_param(it, data.send_data_[0], typename std::integral_constant<bool, second_param_six_characters>());
		}

		if(data.send_data_.size() > 1)
		{ 
			*it++ = field_delimiter;
			it = std::copy(value_specifier, value_specifier + sizeof(value_specifier) - 1, it);
			*it++ = field_delimiter;
			it = format_param(it, data.send_data_[1], typename std::integral_constant<bool, second_param_six_characters>());
		}

		it = std::copy(packet_terminator, packet_terminator + sizeof(packet_terminator) -1, it);

		return it;			
	}
	static buf_type::iterator format_param(buf_type::iterator it, int param, std::true_type)
	{
		const std::string &tmp = hex_conversion::convert_hex<6>(param);
		return std::copy(tmp.begin(), tmp.end(), it);
	}
	static buf_type::iterator format_param(buf_type::iterator it, int param, std::false_type)
	{
		const std::string &tmp = hex_conversion::convert_hex<2>(param);
		return std::copy(tmp.begin(), tmp.end(), it);
	}
};


template<typename Packet_Storage, bool second_param_six_characters = false>
class serialize_max_2_params_and_go_policy
{
public:
	static buf_type::iterator serialize(buf_type::iterator it, const Packet_Storage &data)
	{
		it = serialize_max_2_params_policy<Packet_Storage, second_param_six_characters>::serialize(it, data);
		it = std::copy(header_names[go], (header_names[go] + std::strlen(header_names[go])), it);	
		it = std::copy(packet_terminator, packet_terminator + sizeof(packet_terminator) -1, it);
		return it;
	}
};

template<typename Packet_Storage>
class serialize_iterator_policy
{
public:
	static buf_type::iterator serialize(buf_type::iterator it, const Packet_Storage &data)
	{
		it = std::copy(data.send_data_.begin(), data.send_data_.end(), it);	
		it = std::copy(packet_terminator, packet_terminator + sizeof(packet_terminator) -1, it);
		return it;
	}
};

}}