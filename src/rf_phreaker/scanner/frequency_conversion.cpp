#include "rf_phreaker/scanner/frequency_conversion.h"
#include "rf_phreaker/common/common_utility.h"

#include <boost/math/special_functions.hpp>

using namespace rf_phreaker;
using namespace rf_phreaker::scanner::lms;
using namespace rf_phreaker::scanner;

const double frequency_conversion::n_fract_multiplier_ = std::pow(2.0, 23.0);

frequency_conversion::frequency_conversion(frequency_type reference_clock)
	: pll_reference_clock_(reference_clock)
{
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(232500000, freq_select(232500000, 0x27)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(285625000, freq_select(285625000, 0x2F)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(336875000, freq_select(336875000, 0x37)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(405000000, freq_select(405000000, 0x3F)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(465000000, freq_select(465000000, 0x26)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(571250000, freq_select(571250000, 0x2E)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(673750000, freq_select(673750000, 0x36)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(810000000, freq_select(810000000, 0x3E)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(930000000, freq_select(930000000, 0x25)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(1142500000, freq_select(1142500000, 0x2D)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(1347500000, freq_select(1347500000, 0x35)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(1620000000, freq_select(1620000000, 0x3D)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(1860000000, freq_select(1860000000, 0x24)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(2285000000, freq_select(2285000000, 0x2C)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(2695000000, freq_select(2695000000, 0x34)));
	freq_selects_.insert(std::make_pair<frequency_type, freq_select>(3240000000, freq_select(3240000000, 0x3C)));
}


frequency_conversion::~frequency_conversion(void)
{
}

packet_container frequency_conversion::convert_to_packet_container(frequency_type freq)
{
	lms_freq l_freq = convert_to_lms_freq(freq);

	packet_container container;

	container.add_packet(std::make_shared<lime_write_packet>(rx_nint_register, nint_register_value(l_freq.nint_)));
	container.add_packet(std::make_shared<lime_write_packet>(rx_nfractional_msb_register, fractional_msb_register_value(l_freq.nint_, l_freq.nfrac_)));
	container.add_packet(std::make_shared<lime_write_packet>(rx_nfractional_middle_register, fractional_middle_register_value(l_freq.nfrac_)));
	container.add_packet(std::make_shared<lime_write_packet>(rx_nfractional_lsb_register, fractional_lsb_register_value(l_freq.nfrac_)));
	container.add_packet(std::make_shared<lime_write_packet>(rx_freq_select_register, freq_select_register_value(freq, l_freq.freq_select_)));

	return container;
}
	
lms_freq frequency_conversion::convert_to_lms_freq(frequency_type freq)
{
	auto freq_select_it = freq_selects_.lower_bound(freq);

	if(freq_select_it == freq_selects_.end())
		throw misc_error(str(boost::format("Error converting frequency.  Frequency (%d) is too large.") % freq));

	else if(freq_select_it != freq_selects_.begin())
		--freq_select_it;

	else if(freq < 0)
		throw misc_error(str(boost::format("Error converting frequency.  Frequency (%d) is too small.") % freq));


	auto freq_select = freq_select_it->second;
	
	double freq_mhz = freq / 1e6;

	double tmp_nint = (freq_select.x_ * freq_mhz) / (pll_reference_clock_ / 1e6);

	lms_freq l_freq;
	
	l_freq.nint_ = static_cast<uint16_t>(tmp_nint);

	l_freq.nfrac_ = static_cast<int>(n_fract_multiplier_ * (tmp_nint - l_freq.nint_));

	l_freq.freq_select_ = freq_select.freq_select_;

	l_freq.reference_ = static_cast<uint32_t>(pll_reference_clock_);

	l_freq.x_ = static_cast<uint8_t>(freq_select.x_);

	return l_freq;
}
	
uint8_t frequency_conversion::nint_register_value(int nint)
{
	return static_cast<uint8_t>(nint >> 1);
}

uint8_t frequency_conversion::fractional_msb_register_value(int nint, int nfractional)
{
	uint8_t t1 = static_cast<uint8_t>(nint << 7);
	uint8_t t2 = static_cast<uint8_t>(nfractional >> 16) & 0x7F;
	return t1 | t2;
}

uint8_t frequency_conversion::fractional_middle_register_value(int nfractional)
{
	return static_cast<uint8_t>((nfractional >> 8));
}

uint8_t frequency_conversion::fractional_lsb_register_value(int nfractional)
{
	return static_cast<uint8_t>(nfractional);
}

uint8_t frequency_conversion::freq_select_register_value(rf_phreaker::frequency_type freq, uint8_t select)
{
	return static_cast<uint8_t>((select << 2) | 
		(freq < mhz(1500) ? first_buffer_enabled : second_buffer_enabled));
}

frequency_type frequency_conversion::convert_to_hz(const lms_freq &lfreq)
{
    uint64_t pll_coeff = (((uint64_t)lfreq.nint_) << 23) + lfreq.nfrac_;
    uint32_t div = (lfreq.x_ << 23);

    auto f = (double)(((lfreq.reference_ * pll_coeff) + (div >> 1)) / div);

	return (frequency_type)boost::math::round(f / 100) * 100;
}

