#pragma once

#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/common/measurements.h"
#include "boost/utility/binary.hpp"
#include "boost/icl/interval_map.hpp"
#include <map>

namespace rf_phreaker { namespace scanner {


struct rf_switch
{
	rf_switch(frequency_type low_freq, frequency_type high_freq, int32_t setting)
		: setting_(setting)
	{
		path_.start_freq_ = low_freq;
		path_.end_freq_ = high_freq;
	}
	frequency_path path_;
	int32_t setting_;
};

class rf_switch_conversion
{
public:
	rf_switch_conversion(void)
	{
		switches_.push_back(rf_switch(mhz(700), mhz(760), BOOST_BINARY(001 0100 001 0000 0000)));
		switches_.push_back(rf_switch(mhz(921), mhz(960), BOOST_BINARY(001 1010 010 0000 0000)));
		switches_.push_back(rf_switch(mhz(1805), mhz(1880), BOOST_BINARY(001 1111 010 0000 0000)));
		switches_.push_back(rf_switch(mhz(2110), mhz(2170), BOOST_BINARY(001 0100 100 0000 0000)));
		switches_.push_back(rf_switch(mhz(2600), mhz(2700), BOOST_BINARY(001 1110 100 0000 0000)));
	}

	~rf_switch_conversion(void) {}

	uint32_t convert_to_gpio(frequency_type freq, bandwidth_type bw, uint32_t current_gpio)
	{
		// Least significant byte is used by Nuand.  Remove everything else.
		auto new_gpio = current_gpio & 0xFF;

		//auto upper_freq = freq + static_cast<frequency_type>(bw / 2.0);
		//auto lower_freq = freq - static_cast<frequency_type>(bw / 2.0);
		// Currently no overlaps so we only need to look at one lookup.

		rf_switch *rf_sw = nullptr;
		for(auto &sw : switches_) {
			if(freq <= sw.path_.end_freq_ && freq >= sw.path_.start_freq_) {
				rf_sw = &sw;
				break;
			}
		}

		if(rf_sw != nullptr)
			new_gpio |= rf_sw->setting_;
		else {
			LOG_L(WARNING) << "Frequency (" << freq / 1e6 << "mhz) and bandwidth (" << bw / 1e6 << "mhz) is outside the available RF paths.";
		}
		return new_gpio;
	}

	std::vector<rf_switch> switches_;
};

}}
