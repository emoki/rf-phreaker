#pragma once

#include "ipp.h"
#include "rf_phreaker/ipp_custom/ipp_helper.h"

#include <stdint.h>
#include <assert.h>
#include <stdexcept>
#include <fstream>


template<typename D>
class ipp_array;

typedef ipp_array<Ipp32fc> ipp_32fc_array;
typedef ipp_array<Ipp32f> ipp_32f_array;
typedef ipp_array<Ipp16sc> ipp_16sc_array;


inline std::ostream& operator <<(std::ostream &os, const Ipp32fc &t);
inline std::istream& operator >>(std::istream &is, Ipp32fc &t);
inline std::ostream& operator <<(std::ostream &os, const Ipp16sc &t);
inline std::istream& operator >>(std::istream &is, Ipp16sc &t);
template<typename DataType> inline std::ostream& operator <<(std::ostream &os, const ipp_array<DataType> &t);
template<typename DataType> inline std::istream& operator >>(std::istream &is, ipp_array<DataType> &t);

template<typename DataType>
class ipp_array
{
public:
	ipp_array(int length = 0);

	ipp_array(const DataType *data, int length);

	ipp_array(const ipp_array& other);
	
	ipp_array(ipp_array&& other);

	~ipp_array(void);

	ipp_array& operator=(ipp_array other);

	void swap(ipp_array &other);

	void reset(int length);

	void set_array_values(DataType value);

	void copy(const DataType *data, int data_length);

	const DataType * get(int position = 0) const;

	DataType * get(int position = 0);

	DataType get_value(int position) const;

	int length() const;

	ipp_array create_shallow_copy(int offset) const;

	DataType& operator [](int position) { return array_[position]; }

	const DataType& operator [](int position) const { return array_[position]; }

	typedef DataType data_type_;

	void output_text(const std::string &filename = "ipp_array.txt") const;

	void output_binary(const std::string &filename = "ipp_array.txt") const;

private:
	void allocate(int length);

	void allocate_(int length);

	void deallocate();

	int length_;

	DataType *array_;

	bool shallow_copy_;
};

template<typename DataType> ipp_array<DataType>::ipp_array(int length)
	: length_(0)
	, array_(0)
	, shallow_copy_(/*true*/false)
{
	if(length)
		reset(length);
}

template<typename DataType> ipp_array<DataType>::ipp_array(const DataType *data, int length)
	: length_(0)
	, array_(0)
	, shallow_copy_(/*true*/false)
{
	reset(length);
	copy(data, length);
}

template<typename DataType> ipp_array<DataType>::ipp_array(const ipp_array& other)
	: shallow_copy_(/*true*/other.shallow_copy_)
	, array_(0)
	, length_(0)
{
	if(other.shallow_copy_)
	{
		array_ = other.array_;
		length_ = other.length_;
	}
	else
	{
		reset(other.length_);
		copy(other.array_, length_);
	}
}

template<typename DataType> ipp_array<DataType>::ipp_array(ipp_array&& other)
	: shallow_copy_(false)
	, array_(0)
	, length_(0)
{
	swap(other);
}

template<typename DataType> ipp_array<DataType>::~ipp_array()
{
	if(!shallow_copy_)
		deallocate();
}

template<typename DataType>	ipp_array<DataType>& ipp_array<DataType>::operator = (ipp_array other)
{
	other.swap(*this);
	return *this;
}

template<typename DataType> void ipp_array<DataType>::swap(ipp_array &other)
{
	std::swap(other.length_, length_);
	std::swap(other.array_, array_);
	std::swap(other.shallow_copy_, shallow_copy_);
}

template<typename DataType> inline void ipp_array<DataType>::deallocate()
{
	ippFree(array_);
	array_ = 0;
}

template<typename DataType> void ipp_array<DataType>::reset(int length)
{
	assert(length >= 0);

	if(length_ != length)
	{
		if(!shallow_copy_)
			deallocate();
		allocate(length);
		length_ = length;
	}
}

template<typename DataType> inline void ipp_array<DataType>::allocate(int length)
{
	shallow_copy_ = false;
	allocate_(length);
}

template<> inline void ipp_array<Ipp16sc>::allocate_(int length)
{
	array_ = ippsMalloc_16sc(length);
	if(array_ == 0)
		throw std::runtime_error("Unable to construct Ipp16s ipp_array.\n");
}

template<> inline void ipp_array<Ipp32fc>::allocate_(int length)
{
	array_ = ippsMalloc_32fc(length);
	if(array_ == 0)
		throw std::runtime_error("Unable to construct Ipp32fc ipp_array.\n");
}

template<> inline void ipp_array<Ipp8u>::allocate_(int length)
{
	array_ = ippsMalloc_8u(length);
	if(array_ == 0)
		throw std::runtime_error("Unable to construct Ipp8u ipp_array.\n");
}

template<> inline void ipp_array<Ipp32f>::allocate_(int length)
{
	array_ = ippsMalloc_32f(length);
	if(array_ == 0)
		throw std::runtime_error("Unable to construct Ipp32f ipp_array.\n");
}

template<> inline void ipp_array<Ipp16sc>::set_array_values(Ipp16sc value)
{
	ipp_helper::check_status(ippsSet_16sc(value, array_, length_));
}

template<> inline void ipp_array<Ipp32fc>::set_array_values(Ipp32fc value)
{
	ipp_helper::check_status(ippsSet_32fc(value, array_, length_));
}

template<> inline void ipp_array<Ipp32f>::set_array_values(Ipp32f value)
{
	ipp_helper::check_status(ippsSet_32f(value, array_, length_));
}

template<typename DataType> DataType * ipp_array<DataType>::get(int position)
{
	assert(position >= 0 && position < length_);

	return &array_[position];
}

template<typename DataType> const DataType * ipp_array<DataType>::get(int position) const 
{
	assert(position >= 0 && position < length_);

	return &array_[position];
}

template<typename DataType> DataType ipp_array<DataType>::get_value(int position) const
{
	assert(position >= 0 && position < length_);

	return array_[position];
}


template<typename DataType>	int ipp_array<DataType>::length() const
{ 
	return length_; 
}

template<typename DataType>	void ipp_array<DataType>::copy(const DataType *data, int data_length)
{
	assert(data_length >= 0);
	
	if(data_length > length_)
		reset(data_length);

	memcpy(array_, data, data_length * sizeof(DataType));
}

template<typename DataType>	ipp_array<DataType> ipp_array<DataType>::create_shallow_copy(int offset) const
{
	assert(offset < length_);

	ipp_array<DataType> data;
	
	data.array_ = &array_[offset];
	
	data.length_ = length_ - offset;

	data.shallow_copy_ = true;

	return data;
};

template<typename DataType> void ipp_array<DataType>::output_text(const std::string &filename) const
{
	std::ofstream file(filename);
	if(file.is_open())
	{
		for(int i = 0; i < length_; ++i)
			file << array_[i] << "\n";
	}
	else
		throw std::runtime_error("Unable to open file for ipp_array output text.");
}

template<typename DataType> void ipp_array<DataType>::output_binary(const std::string &filename) const
{
	std::ofstream file(filename, std::ios::binary);
	if(file.is_open())
		file.write(reinterpret_cast<const char*>(array_), length() * sizeof(data_type_));
	else
		throw std::runtime_error("Unable to open file for ipp_array output binary.");
}
 

inline std::ostream& operator <<(std::ostream &os, const Ipp32fc &t)
{
	os << t.re << "\t" << t.im;
	return os;
}

inline std::istream& operator >>(std::istream &is, Ipp32fc &t)
{
	is >> t.re;
	is >> t.im;
	return is;
}

inline std::ostream& operator <<(std::ostream &os, const Ipp16sc &t)
{
	os << t.re << "\t" << t.im;
	return os;
}

inline std::istream& operator >>(std::istream &is, Ipp16sc &t)
{
	is >> t.re;
	is >> t.im;
	return is;
}


template<typename DataType>
inline std::ostream& operator <<(std::ostream &os, const ipp_array<DataType> &t)
{
	auto length = t.length();
	os << length << "\n";
	for(int i = 0; i < length; ++i)
		os << t.get()[i] << "\n";
	return os;
}

template<typename DataType>
inline std::istream& operator >>(std::istream &is, ipp_array<DataType> &t)
{
	int length = 0;
	is >> length;
	t.reset(length);
	for(int i = 0; i < length; ++i)
		is >> t.get()[i];
	return is;
}
