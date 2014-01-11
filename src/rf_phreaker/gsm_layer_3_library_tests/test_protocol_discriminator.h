#pragma once

#include "rf_phreaker/gsm_layer_3_library_tests/test_info_element.h"

class test_protocol_discriminator : public test_info_element
{
public:
	test_protocol_discriminator(void);
	~test_protocol_discriminator(void);
private:
	void decode_good_bit_stream();

	void decode_bit_stream_bad_verification();

};

