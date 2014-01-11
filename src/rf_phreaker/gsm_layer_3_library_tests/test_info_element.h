#pragma once

#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"
#include <boost/assert.hpp>

class test_info_element
{
public:
	test_info_element(void);
	~test_info_element(void);

	void run_automated_tests();

private:
	virtual void decode_good_bit_stream() = 0;

	virtual void decode_bit_stream_bad_verification() = 0;
};

