// test_gsm_layer_3_library.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "rf_phreaker/gsm_layer_3_library_tests/test_l2_pseudo_length_element.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_gsm_bit_stream.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_generic_information_element.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_3_message.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_message.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_ter_message.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_system_information_type_2_quarter_message.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_skip_indicator.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_protocol_discriminator.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_cell_identity.h"
#include "rf_phreaker/gsm_layer_3_library_tests/test_location_area_identification.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		test_gsm_bit_stream bs;
		bs.run_automated_tests();

		test_generic_information_element::run_automated_tests();

		test_l2_pseudo_length_element l2;
		l2.run_automated_tests();

		test_skip_indicator skip;
		skip.run_automated_tests();

		test_protocol_discriminator proto;
		proto.run_automated_tests();

		test_cell_identity cid;
		cid.run_automated_tests();

		//test_location_area_identification lai;
		//lai.run_automated_tests();

		test_system_information_type_3_message si3;
		si3.run_automated_tests();

		test_system_information_type_2_message si2;
		si2.run_automated_tests();

		test_system_information_type_2_ter_message si2_ter;
		si2_ter.run_automated_tests();

		test_system_information_type_2quarter_message si2_quarter;
		si2_quarter.run_automated_tests();


	}
	catch(std::exception &err)
	{
		std::cout << err.what();
		char c;
		std::cin >> c;
	}
	return 0;
}

