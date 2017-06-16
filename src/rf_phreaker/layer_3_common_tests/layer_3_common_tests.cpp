// test_layer_3_common.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rf_phreaker/layer_3_common_tests/test_uint16_string.h"
#include "rf_phreaker/layer_3_common_tests/aggregate_tests.h"

int main(int argc, char* argv[])
{
	test_uint16_string test;
	test.run_automated_tests();

	aggregate_tests agg_tests;
	agg_tests.run_automated_tests();
	
	return 0;
}

