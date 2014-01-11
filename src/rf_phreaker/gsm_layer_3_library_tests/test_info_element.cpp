#include "rf_phreaker/gsm_layer_3_library_tests/test_info_element.h"


test_info_element::test_info_element(void)
{
}


test_info_element::~test_info_element(void)
{
}

void test_info_element::run_automated_tests()
{
	decode_good_bit_stream();
	decode_bit_stream_bad_verification();
}
