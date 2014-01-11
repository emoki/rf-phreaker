#pragma once

#include "rf_phreaker/scanner/scanner_types.h"
#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/packet_helper.h"
#include "rf_phreaker/scanner/scanner_utility.h"

#define ENABLE_PACKET_DEBUG

namespace rf_phreaker { namespace scanner {

template<typename T> class generic_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_iterator_policy<T>>
{
public:
	void set_send_data(const typename T::data_type &data)
	{
		T.send_data_ = data;
	}

	const typename T::data_type& get_send_data() const
	{
		return T.send_data_;
	}

	buf_type::iterator parse(buf_type::iterator it)
	{
		//packet_impl::parse(it);
		T.receive_data_.resize(return_bytes_policy_.return_bytes_expected(storage_));
		return std::copy(T.receive_data_.begin(), T.receive_data_.end(), it);
	}

	char* parse(char *it)
	{
		//packet_impl::parse(it);
		T.receive_data_.resize(return_bytes_policy_.return_bytes_expected(storage_));
		return std::copy(T.receive_data_.begin(), T.receive_data_.end(), it);
	}

	const buf_type& get_receive_data() const
	{
		return T.receive_data_;
	}
};

// TODO - figure out accelerometer_read return size
template<typename T> class accelerometer_read_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class accelerometer_write_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class calibrate_dds_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class read_1pps_clock_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class dds_reset_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

// TODO - figure out dds_read return size
template<typename T> class dds_read_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class dds_update_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class dds_write_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class set_decimation_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	set_decimation_packet_type() {}
	set_decimation_packet_type(int decimation_value)
		: packet_impl(decimation_value)
	{}

	static const size_t decimation_pos_ = 0;

	int get_decimation_value()
	{
		return storage_.send_data_[decimation_pos_];
	}

	int set_decimation(int decimation)
	{
		storage_.send_data_[decimation_pos_] = decimation;
	}
};

// TODO - figure out eeprom_read return size
template<typename T> class eeprom_read_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class eeprom_write_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class fpga_reset_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

// TODO - do not use go packet directly
//template<typename T> class go_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
//{};

template<typename T> class gps_off_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class gps_on_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class gps_reset_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

// TODO - figure out gps_read return size
template<typename T> class gps_read_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class gps_send_ascii_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class lime_reset_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class lime_read_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	lime_read_packet_type() {}
	lime_read_packet_type(lms_register_type address)
		: packet_impl(address)
	{}

	static const size_t address_pos_ = 0;
	static const size_t recieve_value_pos_ = 0;

	void set_register_address(lms_register_type address) 
	{ 
		storage_.send_data_[address_pos_] = address; 
	}

	lms_register_type get_register_address() const
	{
		return (lms_register_type)storage_.send_data_[address_pos_];
	}

	buf_type::iterator parse(buf_type::iterator it) 
	{ 
		storage_.receive_data_[recieve_value_pos_] = hex_conversion::convert_hex<T::expected_return_bytes_>(it);
		return it + T::expected_return_bytes_; 
	}

	char* parse(char *it) 
	{ 
		storage_.receive_data_[recieve_value_pos_] = hex_conversion::convert_hex<T::expected_return_bytes_>(it);
		return it + T::expected_return_bytes_; 
	}

	lms_value_type get_register_value() const { return (lms_value_type)storage_.receive_data_[recieve_value_pos_]; }
};

template<typename T> class lime_write_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	lime_write_packet_type() {}
	lime_write_packet_type(int address, int value)
		: packet_impl(address, value)
	{}

	static const size_t address_pos_ = 0;
	static const size_t value_pos_ = 1;

	typename lime_write_packet_type<T>& set_register_address_and_value(int address, int value)
	{
		storage_.send_data_[address_pos_] = address; 
		storage_.send_data_[value_pos_] = value; 
		return *this;
	}

	void set_register_address(lms_register_type address) 
	{ 
		storage_.send_data_[address_pos_] = address; 
	}

	lms_register_type get_register_address() const
	{
		return (lms_register_type)storage_.send_data_[address_pos_];
	}

	void set_register_value(lms_value_type value)
	{
		storage_.send_data_[value_pos_] = value; 
	}

	lms_value_type get_register_value() const
	{
		return (lms_register_type)storage_.send_data_[value_pos_];
	}
};

template<typename T> class reset_all_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class set_sample_size_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T, true>>
{};

template<typename T> class fpga_status_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class set_switch_channel_select_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	set_switch_channel_select_packet_type(int switch_value)
		: packet_impl(switch_value)
	{}
};

template<typename T> class set_switch_7_9_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	set_switch_7_9_packet_type(int switch_value)
		: packet_impl(switch_value)
	{}
};

template<typename T> class set_switch_input_select_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{
public:
	set_switch_input_select_packet_type(int switch_value)
		: packet_impl(switch_value)
	{}
};

template<typename T> class mem_test_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class usb_reset_packet_type : public packet_impl<T, return_bytes_known_policy<T>, serialize_max_2_params_policy<T>>
{};

template<typename T> class set_sample_size_and_go_packet_type : public packet_impl<T, return_bytes_calc_using_samples_policy<T>, serialize_max_2_params_and_go_policy<T, true>>
{
public:
	set_sample_size_and_go_packet_type() {}
	set_sample_size_and_go_packet_type(int sample_size)
		: packet_impl(sample_size)
	{}

	static const size_t sample_size_pos_ = 0;

	void set_sample_size(int sample_size)
	{
		storage_.send_data_[sample_size_pos_] = sample_size; 
	}

	int get_sample_size()
	{
		return storage_.send_data_[sample_size_pos_];
	}

	buf_type::iterator parse(buf_type::iterator it)
	{ 
		storage_.iq_sample_position_ = static_cast<char*>(&(*it));
		it += get_sample_size();
		return it; 
	}

	char* parse(char *it)
	{ 
		storage_.iq_sample_position_ = it;
		it += get_sample_size();
		return it; 
	}

	char* get_iq()
	{
		return storage_.iq_sample_position_;
	}
	
};

}}