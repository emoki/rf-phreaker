#pragma once

#include <algorithm>
#include <chrono>
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
	gain_manager() : set_point_(1000), increment_(90), expiration_time_(std::chrono::minutes(1))
	{}

	class gain_history
	{
	public:
		gain_history(const measurement_info &meas, double lna_bypass, double lna_mid, double lna_max)
			: freq_(meas.frequency())
			, bw_(find_valid_bandwidth(meas.bandwidth()))
			, gain_(meas.gain())
			, max_adc_(0)
			, lna_bypass_gain_(0)
			, lna_mid_gain_(abs(lna_mid - lna_bypass))
			, lna_max_gain_(abs(lna_max - lna_bypass))
			, last_update_(std::chrono::system_clock::now())
		{
			ipp_helper::check_status(ippsNorm_Inf_32fc32f(meas.get_iq().get(), meas.get_iq().length(), &max_adc_));
			//ipp_helper::check_status(ippsNorm_L2_32fc64f(meas.get_iq().get(), meas.get_iq().length(), &max_adc_));
		}

		double get_total_gain() {
			double lna_gain = 0;
			switch(gain_.lna_gain_) {
			case lms::LNA_MAX:
				lna_gain = lna_max_gain_;
				break;
			case lms::LNA_MID:
				lna_gain = lna_mid_gain_;
				break;
			case lms::LNA_BYPASS:
				default:
					lna_gain = lna_bypass_gain_;
			}
			return gain_.rxvga1_ + gain_.rxvga2_ + lna_gain;
		}

		rf_phreaker::frequency_type freq_;
		rf_phreaker::bandwidth_type bw_;
		gain_type gain_;
		//Ipp64f max_adc_;
		Ipp32f max_adc_;
		double lna_bypass_gain_;
		double lna_mid_gain_;
		double lna_max_gain_;
		std::chrono::system_clock::time_point last_update_;
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

		auto total_gain = (int)std::round(h.get_total_gain() + 20 * log10(set_point_ / h.max_adc_));

		// If the last measurement was saturated bump the gain down a little more so that we can get to 
		// the set point quicker.
		if(h.max_adc_ >= 2047)
			total_gain -= 3;

		// vga2 is only in increments of 3 so we can adjust vga1 to account for that.
		// This is why the starting value for vga1 is 8.  This allows us to decrement it 
		// if necessary.
		auto lna = lms::LNA_BYPASS;
		int vga1 = 5; 
		int vga2 = 0;  

		if(total_gain < h.lna_max_gain_ + vga1 + vga2) {
			if(total_gain < h.lna_mid_gain_ + vga1 + vga2) {
				lna = lms::LNA_BYPASS;
				vga1 = total_gain > 30 ? 30 : std::max(total_gain, 5);
				vga2 = total_gain > 30 ? std::min(total_gain - 30, 30) : 0;
			}
			else {
				lna = lms::LNA_MID;
				auto tmp_gain = (int)std::round(total_gain - h.lna_mid_gain_);
				vga1 = tmp_gain > 30 ? 30 : std::max(tmp_gain, 5);
				vga2 = tmp_gain > 30 ? std::min(tmp_gain - 30, 30) : 0;
			}
		}
		else {
			lna = lms::LNA_MAX;
			auto tmp_gain = (int)std::round(total_gain - h.lna_max_gain_);
			vga1 = tmp_gain > 30 ? 30 : std::max(tmp_gain, 5);
			vga2 = tmp_gain > 30 ? std::min(tmp_gain - 30, 30) : 0;
		}

		auto remainder = vga2 % 3;
		if(remainder != 0) {
			// vga1 will always be 30 if vga2 is being used.
			// Don't subtract from vga1 if vga2 is maxed out.
			vga2 = vga2 + (3 - remainder);
			if(vga2 > 30)
				vga2 = 30;
			else
				vga1 = vga1 - (3 - remainder);
		}

		gain_type gain(lna, vga1, vga2);

		return gain;
	}

	void update_gain(const measurement_info &meas, double lna_bypass, double lna_mid, double lna_max)
	{
		gain_history h(meas, lna_bypass, lna_mid, lna_max);
		auto it = history_.find(h);
		if(it == history_.end())
			history_.insert(std::make_pair(gain_history_key(h), h));
		else
			it->second = h;
	}
	
	bool is_gain_valid(frequency_type freq, bandwidth_type bw) {
		auto it = history_.find(gain_history_key(freq, bw));
		if(it == history_.end())
			return false;
		else
			return  /*std::chrono::duration_cast<std::chrono::seconds>(*/std::chrono::system_clock::now() - it->second.last_update_/*)*/ < expiration_time_;
	}

	std::map<gain_history_key, gain_history, gain_history_sort>  history_;
	Ipp32f set_point_;
	Ipp32f increment_;
	std::chrono::seconds expiration_time_;
};

}}