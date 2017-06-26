#pragma once

#include "ipp.h"
#include "rf_phreaker/common/ipp_helper.h"
#include "rf_phreaker/common/exception_types.h"

#include <stdint.h>
#include <assert.h>
#include <stdexcept>
#include <fstream>

namespace rf_phreaker
{

template<typename D>
class ipp_array;

typedef ipp_array<Ipp32fc> ipp_32fc_array;
typedef ipp_array<Ipp32f> ipp_32f_array;
typedef ipp_array<Ipp16sc> ipp_16sc_array;
typedef ipp_array<Ipp32u> ipp_32u_array;
typedef ipp_array<Ipp16s> ipp_16s_array;


inline std::ostream& operator <<(std::ostream &os, const Ipp32fc &t);
inline std::istream& operator >>(std::istream &is, Ipp32fc &t);
inline std::ostream& operator <<(std::ostream &os, const Ipp16sc &t);
inline std::istream& operator >>(std::istream &is, Ipp16sc &t);
template<typename DataType> inline std::ostream& operator <<(std::ostream &os, const ipp_array<DataType> &t);
template<typename DataType> inline std::istream& operator >>(std::istream &is, ipp_array<DataType> &t);

template<typename DataType>
class ipp_array {
public:
	ipp_array(int length = 0);

	ipp_array(const DataType *data, int length);

	ipp_array(const ipp_array& other);

	ipp_array(ipp_array&& other);

	~ipp_array(void);

	ipp_array& operator=(ipp_array other);

	bool operator==(const ipp_array &a) const;

	void swap(ipp_array &other);

	void reset(int length);

	void set_array_values(DataType value);

	// Data is copied over.  Reallocates the internal array if necessary; internal data is lost in this case.
	void copy(const DataType *data, int data_length);

	// Data is copied over at the offset.  Fails if data reallocation is needed.
	template<typename Class>
	void copy_at(const Class *data, int data_length, int offset);

	const DataType * get(int position = 0) const;

	DataType * get(int position = 0);

	DataType get_value(int position) const;

	int length() const;

	const ipp_array create_shallow_copy(int offset) const;

	DataType& operator [](int position) {
		assert(position >= 0 && position < length_);
		return array_[position]; 
	}

	const DataType& operator [](int position) const {
		assert(position >= 0 && position < length_);
		return array_[position]; 
	}

	typedef DataType data_type_;

	void output_text(const std::string &filename = "ipp_array.txt") const;

	void output_binary(const std::string &filename = "ipp_array.txt") const;

	void output_matlab_compatible_array(const std::string &filename, int columns = 1, int rows = 0) const;

	std::ofstream& output_matlab_compatible_element(std::ofstream& os, const DataType &d) const;

	void zero_out();

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
	, shallow_copy_(/*true*/false) {
	if(length)
		reset(length);
}

template<typename DataType> ipp_array<DataType>::ipp_array(const DataType *data, int length)
	: length_(0)
	, array_(0)
	, shallow_copy_(/*true*/false) {
	reset(length);
	copy(data, length);
}

template<typename DataType> ipp_array<DataType>::ipp_array(const ipp_array& other)
	: length_(0)
	, array_(0)
	, shallow_copy_(/*true*/other.shallow_copy_) {
	if(other.shallow_copy_) {
		array_ = other.array_;
		length_ = other.length_;
	}
	else {
		reset(other.length_);
		copy(other.array_, length_);
	}
}

template<typename DataType> ipp_array<DataType>::ipp_array(ipp_array&& other)
	: length_(0)
	, array_(0)
	, shallow_copy_(false) {
	swap(other);
}

template<typename DataType> ipp_array<DataType>::~ipp_array() {
	if(!shallow_copy_)
		deallocate();
}

template<typename DataType>	ipp_array<DataType>& ipp_array<DataType>::operator = (ipp_array other) {
	other.swap(*this);
	return *this;
}

template<typename DataType>	bool ipp_array<DataType>::operator == (const ipp_array &a) const {
	for(int i = 0; i < length_; ++i) {
		if(array_[i] != a.array_[i])
			return false;
	}
	return true;
}

template<> inline bool ipp_array<Ipp32f>::operator == (const ipp_array &a) const {
	for(int i = 0; i < length_; ++i) {
		if(abs(array_[i] - a.array_[i]) > 0.00000001)
			return false;
	}
	return true;
}

template<>	inline bool ipp_array<Ipp32fc>::operator == (const ipp_array &a) const {
	for(int i = 0; i < length_; ++i) {
		if(abs(array_[i].re - a.array_[i].re) > 0.00000001 || abs(array_[i].im != a.array_[i].im) > 0.00000001)
			return false;
	}
	return true;
}

template<typename DataType> void ipp_array<DataType>::swap(ipp_array &other) {
	std::swap(other.length_, length_);
	std::swap(other.array_, array_);
	std::swap(other.shallow_copy_, shallow_copy_);
}

template<typename DataType> inline void ipp_array<DataType>::deallocate() {
	ippFree(array_);
	array_ = 0;
}

template<typename DataType> void ipp_array<DataType>::reset(int length) {
	assert(length >= 0);

	if(length_ != length) {
		if(!shallow_copy_)
			deallocate();
		allocate(length);
		length_ = length;
	}
}

template<typename DataType> inline void ipp_array<DataType>::allocate(int length) {
	shallow_copy_ = false;
	allocate_(length);
}

template<> inline void ipp_array<Ipp16sc>::allocate_(int length) {
	array_ = ippsMalloc_16sc(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp16s ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp32u>::allocate_(int length) {
	array_ = ippsMalloc_32u(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp32u ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp32fc>::allocate_(int length) {
	array_ = ippsMalloc_32fc(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp32fc ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp8u>::allocate_(int length) {
	array_ = ippsMalloc_8u(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp8u ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp32f>::allocate_(int length) {
	array_ = ippsMalloc_32f(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp32f ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp16s>::allocate_(int length) {
	array_ = ippsMalloc_16s(length);
	if(array_ == 0)
		throw rf_phreaker_error(std::string("Unable to construct Ipp16s ipp_array with length ") + std::to_string(length) + ".");
}

template<> inline void ipp_array<Ipp16sc>::set_array_values(Ipp16sc value) {
	ipp_helper::check_status(ippsSet_16sc(value, array_, length_));
}

template<> inline void ipp_array<Ipp32fc>::set_array_values(Ipp32fc value) {
	ipp_helper::check_status(ippsSet_32fc(value, array_, length_));
}

template<> inline void ipp_array<Ipp32f>::set_array_values(Ipp32f value) {
	ipp_helper::check_status(ippsSet_32f(value, array_, length_));
}

template<typename DataType> DataType * ipp_array<DataType>::get(int position) {
	assert(position >= 0 && position < length_);

	return &array_[position];
}

template<typename DataType> const DataType * ipp_array<DataType>::get(int position) const {
	assert(position >= 0 && position < length_);

	return &array_[position];
}

template<typename DataType> DataType ipp_array<DataType>::get_value(int position) const {
	assert(position >= 0 && position < length_);

	return array_[position];
}

template<typename DataType>	int ipp_array<DataType>::length() const {
	return length_;
}

template<> inline void ipp_array<Ipp16sc>::zero_out() {
	ipp_helper::check_status((ippsZero_16sc(array_, length_)));
}

template<> inline void ipp_array<Ipp32f>::zero_out() {
	ipp_helper::check_status((ippsZero_32f(array_, length_)));
}

template<> inline void ipp_array<Ipp32fc>::zero_out() {
	ipp_helper::check_status((ippsZero_32fc(array_, length_)));
}

template<> inline void ipp_array<Ipp32u>::zero_out() {
	memset(array_, 0, length_ * sizeof(Ipp32u));
}

template<typename DataType>	void ipp_array<DataType>::copy(const DataType *data, int data_length) {
	assert(data_length >= 0);

	if(data_length > length_)
		reset(data_length);

	memcpy(array_, data, data_length * sizeof(DataType));
}

template<typename DataType> template<typename Class>
void ipp_array<DataType>::copy_at(const Class *data, int data_length, int offset) {
	assert(data_length >= 0);

	if(std::is_same<DataType, Class>::value == false)
		throw rf_phreaker::ipp_error("Error using ipp_array::copy_at.  No conversion is possible.");

	if(data_length + offset > length_)
		throw rf_phreaker::ipp_error("Error using ipp_array::copy_at.  Array length is too small.");

	memcpy(&array_[offset], data, data_length * sizeof(DataType));
}

template<> template<>
inline void ipp_array<Ipp32fc>::copy_at(const Ipp32f *data, int data_length, int offset) {
	assert(data_length >= 0);

	if(data_length + offset > length_)
		throw rf_phreaker::ipp_error("Error using ipp_array::copy_at.  Array length is too small.");

	for(int i = 0; i < data_length; ++i) {
		array_[i + offset].re = data[i];
		array_[i + offset].im = 0;
	}
}

template<typename DataType>	const ipp_array<DataType> ipp_array<DataType>::create_shallow_copy(int offset) const {
	assert(offset < length_);

	ipp_array<DataType> data;

	data.array_ = &array_[offset];

	data.length_ = length_ - offset;

	data.shallow_copy_ = true;

	return data;
};

template<typename DataType> void ipp_array<DataType>::output_text(const std::string &filename) const {
	std::ofstream file(filename);
	if(file.is_open()) {
		for(int i = 0; i < length_; ++i)
			file << array_[i] << "\n";
	}
	else
		throw std::runtime_error("Unable to open file for ipp_array output text.");
}

template<typename DataType> void ipp_array<DataType>::output_binary(const std::string &filename) const {
	std::ofstream file(filename, std::ios::binary);
	if(file.is_open())
		file.write(reinterpret_cast<const char*>(array_), length() * sizeof(data_type_));
	else
		throw std::runtime_error("Unable to open file for ipp_array output binary.");
}

template<typename DataType> void ipp_array<DataType>::output_matlab_compatible_array(const std::string &filename, int columns, int rows) const {
	if(rows == 0 && columns == 1) rows = length_;
	if(columns * rows < length_)
		throw file_io_error("Unable to output matlab compatible array with giving columns and rows");

	std::ofstream file(filename);
	if(file.is_open()) {
		for(int i = 0; i < rows; ++i) {
			output_matlab_compatible_element(file, array_[i]);
			for(int j = 1; j < columns; ++j) {
				file << "\t";
				output_matlab_compatible_element(file, array_[rows * j + i]);
			}
			file << "\n";
		}
	}
	else
		throw file_io_error("Unable to open file for ipp_array matlab compatible array.");
}

template<typename DataType> std::ofstream& ipp_array<DataType>::output_matlab_compatible_element(std::ofstream& os, const DataType &d) const {
	os << d;
	return os;
}

template<> inline std::ofstream& ipp_array<Ipp32fc>::output_matlab_compatible_element(std::ofstream& os, const Ipp32fc &d) const {
	os << d.re << (d.im >= 0 ? "+" : "") << d.im << "i";
	return os;
}

template<> inline std::ofstream& ipp_array<Ipp16sc>::output_matlab_compatible_element(std::ofstream& os, const Ipp16sc &d) const {
	os << d.re << (d.im >= 0 ? "+" : "") << d.im << "i";
	return os;
}

inline std::ostream& operator <<(std::ostream &os, const Ipp32fc &t) {
	os << t.re << "\t" << t.im;
	return os;
}

inline std::istream& operator >>(std::istream &is, Ipp32fc &t) {
	is >> t.re;
	is >> t.im;
	return is;
}

inline std::ostream& operator <<(std::ostream &os, const Ipp16sc &t) {
	os << t.re << "\t" << t.im;
	return os;
}

inline std::istream& operator >>(std::istream &is, Ipp16sc &t) {
	is >> t.re;
	is >> t.im;
	return is;
}

template<typename DataType>
inline std::ostream& operator <<(std::ostream &os, const ipp_array<DataType> &t) {
	auto length = t.length();
	os << length << "\n";
	for(int i = 0; i < length; ++i)
		os << t.get()[i] << "\n";
	return os;
}

template<typename DataType>
inline std::istream& operator >>(std::istream &is, ipp_array<DataType> &t) {
	int length = 0;
	is >> length;
	t.reset(length);
	for(int i = 0; i < length; ++i)
		is >> t.get()[i];
	return is;
}

}