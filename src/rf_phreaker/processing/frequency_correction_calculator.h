#pragma once
#include <set>
#include <map>
#include "rf_phreaker/umts_analysis/umts_analysis.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/common/settings.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/common/log.h"

namespace rf_phreaker { namespace processing {

struct correction_lookup
{
	correction_lookup() : has_insertions_(false) {}

	void insert(int cpich, double ecio, int freq_shift) {
		auto it = cpichs_.find(cpich);
		if(it == cpichs_.end()) {
			ecio_freq_shift_group_type tmp;
			it = cpichs_.insert(std::make_pair(cpich, tmp)).first;
		}
		it->second.insert(std::make_pair(ecio, freq_shift));
		has_insertions_ = true;
	}

	int find_best_freq_shift() {
		int freq_shift = 0;
		if(cpichs_.size()) {
			for(auto &ecio_freq : cpichs_) {
				freq_shift += ecio_freq.second.begin()->second;
			}
			freq_shift /= (int)cpichs_.size();
		}
		return freq_shift;
	}

	bool has_insertions() { return has_insertions_; }

	typedef std::multimap<double, int, std::greater<double>> ecio_freq_shift_group_type;
	typedef std::map<int, ecio_freq_shift_group_type> cpich_group_type;
	cpich_group_type cpichs_;
	bool has_insertions_;
};

struct freq_correction_param
{
	umts_scan_type scan_type_;
	double sensitivity_;
	int num_coherent_slots_;
	int start_freq_;
	int end_freq_;
	int increment_;
};

class frequency_correction_calculator
{
public:
	frequency_correction_calculator(double sampling_rate)
		: shifter_(sampling_rate) {}

	frequency_correction_calculator(const frequency_correction_calculator &a) 
		: shifter_(a.shifter_) {}

	double calculate_error(frequency_type shift, frequency_type carrier_freq) {
		return shift * (38.4e6 / carrier_freq);
	}

	correction_lookup determine_freq_correction(raw_signal *info, umts_analysis &analysis, const freq_correction_param &param) {
		correction_lookup correction;

		umts_measurements group;

		analysis.set_num_coherent_slots_for_psch(param.num_coherent_slots_);

		LOG(LDEBUG) << "Starting frequency correction for " << info->frequency() / 1e6 << " MHz. Start offset = " << param.start_freq_ << " Hz. End offset = " << param.end_freq_ << " Hz. Increment = " << param.increment_ << " Hz.";
		for(int i = param.start_freq_; i <= param.end_freq_; i += param.increment_) {
			raw_signal shifted_signal(*info);
			shifter_.shift_frequency(shifted_signal.get_iq(), shifted_signal.get_iq().length(), i);
			auto status = analysis.cell_search(shifted_signal, group, param.sensitivity_, param.scan_type_);
			if(status != 0)
				throw umts_analysis_error("Error processing umts.");

			for(const auto &meas : group) {
				correction.insert(meas.cpich_, meas.ecio_, i);
			}
		}

		return correction;
	}

private:
	frequency_shifter shifter_;

};


}}