#include "rf_phreaker/gsm_layer_3_library/location_area_identification.h"


location_area_identification::location_area_identification(format_of_information_elements format)
	: information_element_type_3(format, location_area_identification_value_bit_size)
{
}


location_area_identification::~location_area_identification(void)
{
}

void location_area_identification::info_element_specific_decode()
{
	decode_mcc();
	decode_mnc();
	decode_lac();
}

void location_area_identification::decode_mcc()
{
	bit_pos_ = mcc_bit_position_;
	mcc_array_[0] = decode_bcd();
	mcc_array_[1] = decode_bcd();
	mcc_array_[2] = decode_bcd();
	mcc_.reset(new layer_3_information::uint16_string(mcc_array_, array_size_));	
}	

void location_area_identification::decode_mnc()
{
	bit_pos_ = mnc_bit_position_;
	mnc_array_[2] = decode_bcd();
	mnc_array_[0] = decode_bcd();
	mnc_array_[1] = decode_bcd();
	mnc_.reset(new layer_3_information::uint16_string(mnc_array_, is_mnc_two_digits() ? array_size_ - 1 : array_size_));
}

bool location_area_identification::is_mnc_two_digits()
{
	// Each element in the array is composed of a bcd, only four digits.  Therefore we compare against 0x0f.
	return mnc_array_[2] == 0x0F;
}

uint8_t location_area_identification::decode_bcd()
{
	uint8_t bcd;
	if(decoding_upper_nibble())
	{
		bcd = raw_bit_stream_[value_byte_position() + byte_pos()] & 0xF0;
		bcd = bcd >> 4;
	}
	else
		bcd = raw_bit_stream_[value_byte_position() + byte_pos()] & 0x0F;

	bit_pos_ += 4;
	
	return bcd;
}

void location_area_identification::decode_lac()
{
	lac_ = raw_bit_stream_[value_byte_position() + lac_byte_position_] << 8 | raw_bit_stream_[value_byte_position() + lac_byte_position_ + 1];
}

bool location_area_identification::decoding_upper_nibble()
{
	return bit_pos_ % 8 >= 4;
}

uint32_t location_area_identification::byte_pos()
{
	return (uint32_t)std::floor(bit_pos_ / 8.0);
}

void location_area_identification::verify()
{
	for(int i = 0; i < array_size_; i++)
	{
		if(is_bcd_valid(mcc_array_[i]) == false)
			throw std::runtime_error("MCC digit is not a valid binary coded decimal (4 bits).");
	}
	for(int i = 0; i < array_size_; i++)
	{
		if(is_bcd_valid(mnc_array_[i]) == false)
		{
			if((is_mnc_two_digits() && i == 2) == false)
				throw std::runtime_error("MNC digit is not a valid binary coded decimal (4 bits).");
		}	
	}

}

bool location_area_identification::is_bcd_valid(uint8_t bcd)
{
	return bcd < 10;
}

