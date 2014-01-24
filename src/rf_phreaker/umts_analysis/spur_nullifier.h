#pragma once

#include "fft_helper.h"
#include <boost/scoped_ptr.hpp>
#include <list>

class spur_nullifier
{
public:
	spur_nullifier(double ecio_threshold_dbm = -8, int signal_length = 1);
	
	~spur_nullifier(void);

	void reset(int signal_length);

	void nullify_spurs(ipp_32fc_array &signal);

private:
	void find_max_and_relative_peaks();

	void sort_peaks();

	void reduce_peaks_if_necessary();

	void null_relative_peaks_within_threshold();

	boost::scoped_ptr<fft_helper> fft_;

	ipp_32fc_array fft_result_;

	ipp_32f_array magnitude_result_;

	int signal_length_;

	std::list<int> peak_positions_;

	int max_peak_position_;

	Ipp32f max_peak_;

	double peak_threshold_;

	std::size_t max_num_peaks_;
};

