#pragma once

#include "rf_phreaker/gsm_layer_3_library/information_element_types.h"
#include "rf_phreaker/layer_3_common/uint16_string.h"
#include <boost/scoped_ptr.hpp>

typedef layer_3_information::uint16_string mobile_country_code_type;
typedef layer_3_information::uint16_string mobile_network_code_type;
typedef uint16_t location_area_code_type;

// 3GPP TS 24.008 version 10.3.0 Release 10 - Table 10.5.3/3GPP TS 24.008: Location Area Identification information element

class location_area_identification : public information_element_type_3
{
public:
	location_area_identification(format_of_information_elements format);

	~location_area_identification();

	void info_element_specific_decode();

	void verify();

	boost::scoped_ptr<mobile_country_code_type> mcc_;

	boost::scoped_ptr<mobile_network_code_type> mnc_;

	location_area_code_type lac_;

private:

	void decode_mcc();

	void decode_mnc();

	void decode_lac();

	bool is_mnc_two_digits();
	
	bool is_bcd_valid(uint8_t bcd);

	uint8_t decode_bcd();

	bool decoding_upper_nibble();	

	uint32_t byte_pos();
	uint32_t bit_pos_;

	static const uint8_t array_size_ = 3;
	uint8_t mcc_array_[array_size_];
	uint8_t mnc_array_[array_size_];

	static const uint8_t mcc_bit_position_ = 0;
	static const uint8_t mnc_bit_position_ = 12;
	static const uint8_t lac_byte_position_ = 3;
};

