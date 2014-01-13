// lte_layer_3_decoder_tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rf_phreaker/lte_layer_3_decoder_tests/lte_decoding_tests.h"

int main(int argc, char* argv[])
{
	lte_decoding_tests decode_tests;
	decode_tests.run_automated_tests();

	return 0;
}

