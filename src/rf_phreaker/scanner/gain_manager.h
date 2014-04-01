#pragma once

#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/common/common_types.h"
#include "ipp.h"




namespace rf_phreaker { namespace scanner {

// Not all bandwidths are created equal.  This will return bandwidth the blade will actually be using when collecting.
inline bandwidth_type find_valid_bandwidth(bandwidth_type bw)
{
	bandwidth_type valid_bw;
	if(bw <= khz(1500)) valid_bw = khz(1500);
	else if(bw <= khz(1750)) valid_bw = khz(1750);
	else if(bw <= khz(2500)) valid_bw = khz(2500);
	else if(bw <= khz(2750)) valid_bw = khz(2750);
	else if(bw <= mhz(3))  valid_bw = mhz(3);
	else if(bw <= khz(3840)) valid_bw = khz(3840);
	else if(bw <= mhz(5))  valid_bw = mhz(5);
	else if(bw <= khz(5500)) valid_bw = khz(5500);
	else if(bw <= mhz(6))  valid_bw = mhz(6);
	else if(bw <= mhz(7))  valid_bw = mhz(7);
	else if(bw <= khz(8750)) valid_bw = khz(8750);
	else if(bw <= mhz(10))  valid_bw = mhz(10);
	else if(bw <= mhz(12))  valid_bw = mhz(12);
	else if(bw <= mhz(14))  valid_bw = mhz(14);
	else if(bw <= mhz(20))  valid_bw = mhz(20);
	else                       valid_bw = mhz(28);

	return valid_bw;
}

class gain_manager
{
public:
	gain_manager() : set_point_(1500), increment_(90)
	{}

	class gain_history
	{
	public:
		gain_history(const measurement_info &meas)
			: freq_(meas.frequency())
			, bw_(find_valid_bandwidth(meas.bandwidth()))
			, gain_(meas.gain())
			, max_adc_(0)
		{		
			ipp_helper::check_status(ippsNorm_Inf_32fc32f(meas.get_iq().get(), meas.get_iq().length(), &max_adc_));
			//ipp_helper::check_status(ippsNorm_L2_32fc64f(meas.get_iq().get(), meas.get_iq().length(), &max_adc_));
		}

		rf_phreaker::frequency_type freq_;
		rf_phreaker::bandwidth_type bw_;
		gain_type gain_;
		//Ipp64f max_adc_;
		Ipp32f max_adc_;
	};

	class gain_history_key
	{
	public:
		gain_history_key(const gain_history &h) : freq_(h.freq_), bw_(h.bw_) {}
		gain_history_key(frequency_type freq, bandwidth_type bw) : freq_(freq), bw_(find_valid_bandwidth(bw)) {}
		rf_phreaker::frequency_type freq_;
		rf_phreaker::bandwidth_type bw_;
	};
	class gain_history_sort
	{
	public:
		bool operator()(const gain_history_key &a, const gain_history_key &b)
		{
			if(a.freq_ == b.freq_)
				return a.bw_ < b.bw_;
			else
				return a.freq_ < b.freq_;
		}
	};

	gain_type default_gain()
	{
		return gain_type(lms::LNA_MAX, 20, 0);
	}

	bool in_history(frequency_type freq, bandwidth_type bw)
	{
		return history_.find(gain_history_key(freq, bw)) != history_.end();
	}
	
	gain_type calculate_new_gain(frequency_type freq, bandwidth_type bw)
	{
		auto it = history_.find(gain_history_key(freq, bw));
		if(it == history_.end())
			return default_gain();

		auto &h = it->second;

		auto diff = set_point_ - h.max_adc_;

		auto total_gain_diff = diff / increment_;

		int new_gain = h.gain_.rxvga1_ + h.gain_.rxvga2_ + (int)total_gain_diff;

		int vga1 = new_gain > 30 ? 30 : std::max(new_gain, 5);
		int vga2 = new_gain > 30 ? std::min(new_gain - 30, 30) : 0;

		gain_type gain(lms::LNA_MAX, vga1, vga2);

		return gain;

	}

	void update_gain(const measurement_info &meas)
	{
		gain_history h(meas);
		auto it = history_.find(h);
		if(it == history_.end())
			history_.insert(std::make_pair(gain_history_key(meas), h));
		else
			it->second = h;
	}
	
	std::map<gain_history_key, gain_history, gain_history_sort>  history_;
	Ipp32f set_point_;
	Ipp32f increment_;
};

}}