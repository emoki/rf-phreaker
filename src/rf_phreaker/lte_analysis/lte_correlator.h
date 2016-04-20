#include <algorithm>
#include "rf_phreaker/common/cross_correlation_incoherent_and_coherent_addition.h"
#include "rf_phreaker/common/sort_peaks.h"
#include "rf_phreaker/common/frequency_shifter.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "rf_phreaker/lte_analysis/lte_synchronization.h"
#include "rf_phreaker/lte_analysis/lte_types.h"

namespace rf_phreaker {


class lte_correlator {
public:
	lte_correlator(frequency_type sampling_rate) {
		set_sampling_rate(sampling_rate);
	}

	frequency_type sampling_rate() const { return sampling_rate_; }

	void set_sampling_rate(frequency_type sampling_rate) {
		sampling_rate_ = sampling_rate;
		std::vector<std::shared_ptr<ipp_32fc_array>> tmp_pss;
		if(sampling_rate != lte_bandwidth_1_4_mhz_sampling_rate) {
			fir_filter filter;
			filter.set_zero_delay(true);
			filter.set_up_down_factor_based_on_sampling_rates(lte_bandwidth_1_4_mhz_sampling_rate, sampling_rate);
			filter.set_taps(6501);
			for(int i = 0; i < pss_num_; ++i) {
				tmp_pss.push_back(std::make_shared<ipp_32fc_array>((int)(pss_sss_length_ * sampling_rate / lte_bandwidth_1_4_mhz_sampling_rate)));
				// Pad pss array so that the resampled template is the correct size.
				ipp_32fc_array pss(pss_sss_length_ + filter.num_samples_delay());
				pss.zero_out();
				ipp_32fc_array tmp(pss_sss_length_);
				generate_PSS(pss.get(), tmp.get(), pss_sss_length_, i);
				filter.filter(pss.get(), tmp_pss.at(i)->get(), filter.num_iterations_required(pss.length()));
			}
		}
		else {
			for(int i = 0; i < pss_num_; ++i) {
				tmp_pss.push_back(std::make_shared<ipp_32fc_array>(pss_sss_length_));
				ipp_32fc_array tmp(pss_sss_length_);
				generate_PSS(tmp_pss.at(i)->get(), tmp.get(), pss_sss_length_, i);
			}
		}
		half_frame_length_ = (int)(sampling_rate_ * .005); // 5 ms
		resampled_template_length_ = (int)(pss_sss_length_ * sampling_rate_ / lte_bandwidth_1_4_mhz_sampling_rate);
		pss_templates_.insert(std::make_pair(0, tmp_pss));

		//// add the cyclic prefix (which repeats the signal)
		//std::vector<std::shared_ptr<ipp_32fc_array>> templates_with_cp;
		//for(int i = 0; i < 2; ++i) {
		//	auto cp_length = 9 * sampling_rate_ / lte_bandwidth_1_4_mhz_sampling_rate;
		//	if(i)
		//		cp_length = 32 * sampling_rate_ / lte_bandwidth_1_4_mhz_sampling_rate;
		//	for(int i = 0; i < 3; ++i) {
		//		auto &pss = pss_templates_.at(0)[j];
		//		auto t1 = std::make_shared<ipp_32fc_array>(pss->length() + cp_length);
		//		t1->copy(pss->get(), pss->length());
		//		t1->copy_at(pss->get(resampled_template_length_ - cp_length), cp_length, resampled_template_length_);
		//		templates_with_cp.push_back(t1);
		//	}
		//}
		// normalize signal
		for(auto &i : pss_templates_.at(0)) {
			ipp_helper::normalize_signal(i->get(), i->length());
		}
	}

	std::map<frequency_type, std::vector<std::shared_ptr<ipp_32fc_array>>>::iterator add_pss_templates(frequency_type intermediate_freq) {
		std::vector<std::shared_ptr<ipp_32fc_array>> tmp;
		auto zero_if = pss_templates_.find(0)->second;
		for(auto &i : zero_if) {
			auto pss = std::make_shared<ipp_32fc_array>(*i.get());
			shifter_.shift_frequency(*pss.get(), pss->length(), (double)intermediate_freq, sampling_rate_);
			tmp.push_back(pss);
		}
		return pss_templates_.insert(std::make_pair(intermediate_freq, tmp)).first;
	}

	void set_signal(const ipp_32fc_array &signal, int num_half_frames, int num_iterations = -1) {
		cc_.set_num_coherent_windows(1);
		// We only want to look for the highest peak - no incoherent or coherent adds so
		// set the iteration length to total length of the search space.
		cc_.set_iteration_length(half_frame_length_);
		if(num_iterations != -1)
			cc_.set_num_iterations(num_iterations);
		cc_.set_input_signal_and_configure_parameters(signal, half_frame_length_ * num_half_frames + resampled_template_length_,
			resampled_template_length_);
		cc_.calculate_average_power();
	}

	std::vector<CORR_RECORD_TYPE> find_pss(frequency_type intermediate_freq) {
		auto pss_templates = get_pss_templates(intermediate_freq);
		std::vector<CORR_RECORD_TYPE> records;
		for(int i = 0; i < 3; ++i) {
			cc_.do_cross_correlation_and_additions(pss_templates.at(i)->get());
			auto corr = cc_.get_result();

			Ipp32f max = 0;
			int max_idx = 0;
			ippsMaxIndx_32f(corr.get(), corr.length(), &max, &max_idx);
			CORR_RECORD_TYPE r;
			r.ID = i;
			r.NormCorr = max;
			r.RMSCorr = cc_.get_rms(max_idx);
			r.StartSampleNum = max_idx;
			records.push_back(r);
		}
		return records;
	}

	std::vector<std::shared_ptr<ipp_32fc_array>>& get_pss_templates(frequency_type intermediate_freq) {
		auto it = pss_templates_.find(intermediate_freq);
		if(it == pss_templates_.end())
			it = add_pss_templates(intermediate_freq);
		return it->second;
	}

private:
	const static int pss_num_ = 3;
	const static int pss_sss_length_ = 128;
	int resampled_template_length_;
	int half_frame_length_;
	frequency_type sampling_rate_;
	std::map<frequency_type, std::vector<std::shared_ptr<ipp_32fc_array>>> pss_templates_;
	cross_correlation_incoherent_and_coherent_addition cc_;
	frequency_shifter shifter_;
};


}



