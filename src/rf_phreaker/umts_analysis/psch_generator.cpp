#include "rf_phreaker/umts_analysis/psch_generator.h"

namespace rf_phreaker {

psch_generator::psch_generator()
: a_(16)
, neg_a_(16)
, psch_(256)
{
	a_[0] = 1;
	a_[1] = 1;
	a_[2] = 1;
	a_[3] = 1;
	a_[4] = 1;
	a_[5] = 1;
	a_[6] = -1;
	a_[7] = -1;
	a_[8] = 1;
	a_[9] = -1;
	a_[10] = 1;
	a_[11] = -1;
	a_[12] = 1;
	a_[13] = -1;
	a_[14] = -1;
	a_[15] = 1;

	for(int i = 0, end = a_.length(); i < end; ++i)
		neg_a_[i] = a_[i] * -1;

	int index = 0;
	
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();

	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();
	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();

	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();

	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();
	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();

	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();

	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();

	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();

	psch_.copy_at(neg_a_.get(), neg_a_.length(), index);
	index += a_.length();

	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
	psch_.copy_at(a_.get(), a_.length(), index);
	index += a_.length();
}

}