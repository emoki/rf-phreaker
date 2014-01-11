#pragma once
#include "rf_phreaker/gsm_layer_3_library_tests/test_info_element.h"

class test_skip_indicator : public test_info_element
{
public:
	test_skip_indicator(void);
	~test_skip_indicator(void);

private:
	void decode_good_bit_stream();

	void decode_bit_stream_bad_verification();

};

