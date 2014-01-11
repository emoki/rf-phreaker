#pragma once

#include "rf_phreaker/layer_3_common/uint16_string.h"

class test_uint16_string
{
public:
	test_uint16_string(void);
	~test_uint16_string(void);

	void run_automated_tests();

private:
	void test_string(const layer_3_information::uint16_string &a, const char *string, size_t string_length);
	size_t calculate_num_characters(size_t string_length_including_null);
};

