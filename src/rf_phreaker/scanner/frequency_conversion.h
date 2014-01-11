#pragma once

#include "rf_phreaker/scanner/packet_container.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/scanner/packet_typedefs.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/scanner_types.h"

#include <boost/utility/binary.hpp>
#include <map>

namespace rf_phreaker { namespace scanner {

class freq_select
{
public:
	freq_select(rf_phreaker::frequency_type freq, uint8_t freq_select)
		: freq_(freq)
		, freq_select_(freq_select) 
	{
		x_ = std::pow(2.0, (freq_select & bits_2_to_0_mask_) - 3); 
	}

	rf_phreaker::frequency_type freq_;
	uint8_t freq_select_;
	double x_;
	static const uint8_t bits_2_to_0_mask_ = 0x07;
};

class frequency_conversion
{
public:
	frequency_conversion(rf_phreaker::frequency_type reference_clock = freq_ref_hz_default);
	~frequency_conversion(void);

	packet_container convert_to_packet_container(rf_phreaker::frequency_type freq);

	lms::lms_freq convert_to_lms_freq(rf_phreaker::frequency_type freq);

	rf_phreaker::frequency_type convert_to_hz(const lms::lms_freq &freq);

private:

	uint8_t nint_register_value(int nint);
	uint8_t fractional_msb_register_value(int nint, int nfractional);
	uint8_t fractional_middle_register_value(int nfractional);
	uint8_t fractional_lsb_register_value(int nfractional);
	uint8_t freq_select_register_value(rf_phreaker::frequency_type freq, uint8_t select);


	std::map<rf_phreaker::frequency_type, freq_select> freq_selects_;

	rf_phreaker::frequency_type pll_reference_clock_;

	uint32_t integer_part_;

	uint32_t fractional_part_;

	static const double n_fract_multiplier_;
};

}}