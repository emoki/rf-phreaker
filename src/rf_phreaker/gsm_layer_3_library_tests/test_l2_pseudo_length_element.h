#pragma once

#include "rf_phreaker/gsm_layer_3_library/l2_pseudo_length_element.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_info_element.h"

class test_l2_pseudo_length_element : public test_info_element
{
public:
	test_l2_pseudo_length_element(void);
	~test_l2_pseudo_length_element(void);
	
private:
	void decode_good_bit_stream();
	void decode_bit_stream_bad_verification();	
};

