#pragma once 

#include "rf_phreaker/scanner/packet.h"
#include "rf_phreaker/scanner/scanner_types.h"

#include <vector>

namespace rf_phreaker { namespace scanner {

class packet_container
{
public:
	typedef std::vector<packet_ptr>::const_iterator const_packet_iterator;

	packet_container() 
	{}

	packet_container(packet_container &&other) 
	{
		std::swap(packets_, other.packets_);
	}

	buf_type::iterator serialize(buf_type::iterator it) 
	{
		std::for_each(packets_.begin(), packets_.end(), [&](packet_ptr& ptr)
		{
			it = ptr->serialize(it);
		});

		return it;
	}

	void parse(buf_type::iterator it)
	{
		std::for_each(packets_.begin(), packets_.end(), [&](packet_ptr& ptr)
		{
			it = ptr->parse(it);
		});

	}

	void parse(char *it)
	{
		std::for_each(packets_.begin(), packets_.end(), [&](packet_ptr& ptr)
		{
			it = ptr->parse(it);
		});

	}

	void add_packet(const packet_ptr &p)
	{
		packets_.push_back(p);
	}

	void add_container(packet_container &&other)
	{
		const size_t size = packets_.size();
		
		packets_.resize(size + other.num_packets());

		const auto new_size = packets_.size();
		
		auto j = 0;
		for(auto i = size; i < new_size; ++i) 
			packets_[i].swap((other.packets_[j++]));
	}

	size_t return_bytes_expected()
	{
		size_t return_bytes = 0;
		std::for_each(packets_.begin(), packets_.end(), [&](packet_ptr& ptr)
		{
			return_bytes += ptr->return_bytes_expected();
		});
		return return_bytes;
	}

	const_packet_iterator begin() const { return packets_.begin(); }

	const_packet_iterator end() const { return packets_.end(); }

	size_t num_packets() const { return packets_.size(); }

	void clear_packets() { packets_.clear(); }

private:
	std::vector<packet_ptr> packets_;
};

}}