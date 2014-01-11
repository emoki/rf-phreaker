#pragma once

#include <memory>
#include <assert.h>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <type_traits>

#include <boost/lexical_cast.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>

#include "rf_phreaker/scanner/scanner_types.h"

namespace rf_phreaker { namespace scanner {

class packet;
typedef std::shared_ptr<packet> packet_ptr;

class packet
{
public:
	virtual buf_type::iterator serialize(buf_type::iterator it) const = 0;
	virtual buf_type::iterator parse(buf_type::iterator it) = 0;
	virtual char* parse(char *it) = 0;
	virtual size_t return_bytes_expected() const = 0;
	virtual ~packet() {};

	/* convenience function used for testing.*/
	virtual std::string serialize_to_string() const = 0;
	/* convenience function used for testing.*/
	virtual buf_type serialize_to_buf_type() const = 0;
};


template<typename packet_storage, typename return_bytes_policy, typename serialize_policy>
class packet_impl : public packet
{
public:
	typedef packet_storage patcket_storage_type;
	typedef return_bytes_policy return_bytes_policy_type;
	typedef serialize_policy serialize_policy_type;

	packet_impl() {};

	packet_impl(int param_0)
	{
		storage_.send_data_[0] = param_0;
	};

	packet_impl(int param_0, int param_1)
	{
		storage_.send_data_[0] = param_0;
		storage_.send_data_[1] = param_1;
	}

	virtual ~packet_impl() {};

	virtual buf_type::iterator serialize(buf_type::iterator it) const
	{		
		return serialize_policy::serialize(it, storage_);
	}

	virtual buf_type serialize_to_buf_type() const
	{
		buf_type buffer;

		buffer.resize(storage_.estimated_serialize_size());

		auto it = serialize_policy::serialize(buffer.begin(), storage_);

		buffer.resize(it - buffer.begin());
		return buffer;
	}

	virtual std::string serialize_to_string() const
	{
		buf_type buf = serialize_to_buf_type();
		return std::string(&buf[0], buf.size());
	}

	virtual buf_type::iterator parse(buf_type::iterator it)
	{ 
		return it; 
	}

	virtual char* parse(char *it)
	{ 
		return it; 
	}

	virtual size_t return_bytes_expected() const
	{
		return return_bytes_policy::return_bytes_expected(storage_);
	}

protected:
	packet_storage storage_;
};

}}