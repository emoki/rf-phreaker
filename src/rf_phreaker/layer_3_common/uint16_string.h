#pragma once

#include <stdint.h>
#include <string>
#include <ostream>
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

namespace layer_3_information
{

class uint16_string
{
public:
	uint16_string();

	uint16_string(const char *a);

	uint16_string(uint16_t a);

	uint16_string(uint8_t* digits, int num_digits);

	uint16_string(/*digit_type*/long **digits, int num_digits);

	void swap(uint16_string &t)
	{
		string_.swap(t.string_);
	}
	
	size_t num_characters() const
	{
		return string_.length();
	}

	uint16_t to_uint16() const
	{
		return boost::lexical_cast<uint16_t>(string_.c_str());
	}

	const char* to_string() const
	{
		return string_.c_str();
	}

	uint16_string& operator= (const uint16_string &a)
	{
		string_ = a.string_;
		return *this;
	}

	uint16_string& operator= (const std::string &a)
	{
		string_ = a;
		return *this;
	}

	uint16_string& operator= (const uint16_t a)
	{
		string_ = boost::lexical_cast<std::string>(a);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream &os, const uint16_string &a);

	friend std::istream& operator>>(std::istream &is, uint16_string &a);

private:
	std::string string_;
};

inline bool operator == (const uint16_string &a, const uint16_string &b)
{
	return a.to_string() == b.to_string() && a.to_uint16() == b.to_uint16();
}

inline bool operator != (const uint16_string &a, const uint16_string &b)
{
	return !(a == b);
}

inline bool operator == (const uint16_string &a, uint16_t b)
{
	return a.to_uint16() == b;
}

inline bool operator != (const uint16_string &a, uint16_t b)
{
	return !(a == b);
}

inline std::ostream& operator<<(std::ostream &os, const uint16_string &a)
{
	os << a.to_string();
	return os;
}

inline std::istream& operator>>(std::istream &is, uint16_string &a)
{
	is >> a.string_;
	return is;
}

}
