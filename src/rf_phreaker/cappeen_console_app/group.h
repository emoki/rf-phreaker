#pragma once

#include <vector>
#include <stdint.h>

namespace cappeen_scanner {


template<typename Data>
class group
{
public:
	group()
	{}

	template<typename container>
	group(const container &tmp)
	{
		for(uint32_t i = 0; i < tmp.num_elements_; i++)
			internal_data_.push_back(tmp.elements_[i]);
	}

	const Data& get_element(std::size_t i) const
	{
		return internal_data_.at(i);
	}

	Data& get_element(std::size_t i)
	{
		return internal_data_.at(i);
	}

	void set_element(std::size_t pos, Data data)
	{
		internal_data_.at(pos) = data; 
	}

	group& operator =(group const &a)
	{
		internal_data_ = a.internal_data_;
		return *this;
	}

	void resize(std::size_t i) { internal_data_.resize(i); }

	uint32_t size() const { return internal_data_.size(); } 

	void clear() { internal_data_.clear(); }

private:
	std::vector<Data> internal_data_;
};


}