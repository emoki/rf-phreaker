#pragma once

#include "rf_phreaker/common/ipp_array.h"

class psch_generator
{
public:
	psch_generator();

	int psch_length() const { return psch_.length(); }

	const Ipp32fc* psch_ptr() const { return psch_.get(); }

	const ipp_32fc_array& psch() const { return psch_; }

private:
	ipp_32f_array a_;
	
	ipp_32f_array neg_a_;

	ipp_32fc_array psch_;
};