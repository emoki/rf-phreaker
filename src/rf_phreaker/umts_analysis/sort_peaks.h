#include "rf_phreaker/ipp_custom/ipp_array.h"


struct sort_peaks_ascending
{
	sort_peaks_ascending(const ipp_32f_array &magnitude)
		: magnitude_(magnitude)
	{}

	inline bool operator() (int a, int b)
	{
		return magnitude_.get_value(a) < magnitude_.get_value(b);
	}

	const ipp_32f_array &magnitude_;
};

struct sort_peaks_descending
{
	sort_peaks_descending(const ipp_32f_array &magnitude)
		: magnitude_(magnitude)
	{}

	inline bool operator() (int a, int b)
	{
		return magnitude_.get_value(a) > magnitude_.get_value(b);
	}

	const ipp_32f_array &magnitude_;
};
