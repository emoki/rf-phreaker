#pragma once

#include "rf_phreaker/umts_layer_3_decoder/segmented_sib.h"

class test_segmented_sib
{
public:
	test_segmented_sib(void);
	~test_segmented_sib(void);

	void run_automated_tests();

private:
	void combine_two_padded_segments();
	void combine_four_padded_segments();
};

