#pragma once

namespace rf_phreaker {

class gsm_config {
public:
	gsm_config()
		: preform_sync_correlations_(false)
		, sampling_rate_(4875000)
		, clock_rate_(4875000)
		, band_pow_(25)
		, side_pow_(5)
		, bandwidth_(5000000) {
		max_signal_length_ = (int)(sampling_rate_ * 0.060);
	}

	gsm_config(bool preform_sync_correlations, int sampling_rate, int clock_rate, int max_signal_length, int side_pow, int band_pow, int bw)
		: preform_sync_correlations_(preform_sync_correlations)
		, sampling_rate_(sampling_rate)
		, clock_rate_(clock_rate)
		, max_signal_length_(max_signal_length) 
		, band_pow_(band_pow)
		, side_pow_(side_pow)
		, bandwidth_(bw) {}

	bool preform_sync_correlations() const { return preform_sync_correlations_; }
	int max_signal_length() const { return max_signal_length_; }
	int sampling_rate() const { return sampling_rate_; }
	int bandwidth() const { return bandwidth_; }
	int clock_rate() const { return clock_rate_; }
	int band_pow() const { return band_pow_; }
	int side_pow() const { return side_pow_; }

	void preform_sync_correlations(bool preform_sync_correlations) { preform_sync_correlations_ = preform_sync_correlations; }
	void max_signal_length(int max_signal_length) { max_signal_length_ = max_signal_length; }
	void sampling_rate(int sampling_rate) { sampling_rate_ = sampling_rate; }
	void bandwidth(int bandwidth) { bandwidth_ = bandwidth; }
	void clock_rate(int clock_rate) { clock_rate_ = clock_rate; }
	void band_pow(int band_pow) { band_pow_ = band_pow; }
	void side_pow(int side_pow) { side_pow_ = side_pow; }

private:
	bool preform_sync_correlations_;
	int max_signal_length_;
	int sampling_rate_;
	int bandwidth_;
	int clock_rate_;
	int band_pow_;
	int side_pow_;
};

}