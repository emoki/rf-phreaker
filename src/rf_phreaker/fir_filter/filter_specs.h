#pragma once

#include <fstream>
#include <ostream>
#include <istream>

namespace rf_phreaker {

template<typename ArrayType>
class filter_specs
{
public:
	filter_specs(void) : up_factor_(0), down_factor_(0) {}

	filter_specs(const char *filename) {
		std::ifstream file(filename);
		
		if(!file)
			throw std::runtime_error("Unable to read config file for filter_specs.");

		file >> *this;
	}

	~filter_specs(void) {}

	int up_factor() const { return up_factor_; }
	
	int down_factor() const { return down_factor_; }

	const ArrayType& taps() const { return taps_; } 

	void set_taps(ArrayType &data) { taps_ = data; }

	template<typename ArrayType>
	friend std::ostream& operator<<(std::ostream &out, const filter_specs<typename ArrayType> &specs);

	template<typename ArrayType>
	friend std::istream& operator>>(std::istream  &in , filter_specs<typename ArrayType> &specs);

private:
	int up_factor_;

	int down_factor_;

	//int up_phase_;

	//int down_phase_;

	ArrayType taps_;

	//ArrayType delay_line_;

};


template<typename ArrayType>
std::ostream& operator<<(std::ostream &out, const filter_specs<ArrayType> &specs)
{
	out << specs.up_factor_ << std::endl;
	out << specs.down_factor_ << std::endl;
	out << specs.taps_.length() << std::endl;
	for(int i = 0; i < specs.taps_.length(); ++i)
		out << specs.taps_[i] << std::endl;
	return out;
}

template<typename ArrayType>
std::istream& operator>>(std::istream  &in , filter_specs<ArrayType> &specs)
{
	in >> specs.up_factor_;
	in >> specs.down_factor_;
	int length; 
	in >> length;
	specs.taps_.reset(length);
	for(int i = 0; i < length; ++i)
		in >> specs.taps_[i];
	return in;
}

}