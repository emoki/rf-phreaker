#pragma once

#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"



class test_gsm_bit_stream : public gsm_bit_stream
{
public:
	test_gsm_bit_stream(const uint8_t *bit_stream, uint32_t num_bytes, uint32_t bits_unused, uint32_t bits_consumed_thus_far = 0);
	test_gsm_bit_stream(uint32_t bits_consumed = 0);
	~test_gsm_bit_stream();

	void run_automated_tests();

	static const size_t bs_size_ = 23;

	static uint8_t test_bit_stream_[bs_size_];



};

