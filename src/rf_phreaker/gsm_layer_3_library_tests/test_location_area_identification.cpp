#include "rf_phreaker/gsm_layer_3_library_tests/test_location_area_identification.h"
#include "rf_phreaker/gsm_layer_3_library/location_area_identification.h"

test_location_area_identification::test_location_area_identification(void)
{
}


test_location_area_identification::~test_location_area_identification(void)
{
}

void test_location_area_identification::decode_good_bit_stream()
{
	// test with a three digit mnc
	{
		mobile_country_code_type mcc("411");
		mobile_network_code_type mnc("026");
		location_area_code_type lac = 55432;
		test_gsm_bit_stream bs;

		bs.test_bit_stream_[0] = 0x14;
		bs.test_bit_stream_[1] = 0x61;
		bs.test_bit_stream_[2] = 0x20;
		bs.test_bit_stream_[3] = lac >> 8;
		bs.test_bit_stream_[4] = lac & 0xFF;

	
		location_area_identification lai(value_only_format);
	
		lai.decode(bs);
	
		bool threw_error = false;
		try { lai.verify(); } catch(std::exception err) { threw_error = true; }

		BOOST_ASSERT(threw_error == false);
		BOOST_ASSERT(*(lai.mcc_) == (mcc));
		BOOST_ASSERT(*lai.mnc_ == (mnc));
		BOOST_ASSERT(lai.lac_ == lac);
	}

	// Test with a two digit mnc.
	{
		mobile_country_code_type mcc("411");
		mobile_network_code_type mnc("26");
		location_area_code_type lac = 55432;
		test_gsm_bit_stream bs;

		bs.test_bit_stream_[0] = 0x14;
		bs.test_bit_stream_[1] = 0xF1;
		bs.test_bit_stream_[2] = 0x62;
		bs.test_bit_stream_[3] = lac >> 8;
		bs.test_bit_stream_[4] = lac & 0xFF;

	
		location_area_identification lai(value_only_format);
	
		lai.decode(bs);
	
		bool threw_error = false;
		try { lai.verify(); } catch(std::exception err) { threw_error = true; }

		BOOST_ASSERT(threw_error == false);
		BOOST_ASSERT(*lai.mcc_ == (mcc));
		BOOST_ASSERT(*lai.mnc_ == (mnc));
		BOOST_ASSERT(lai.lac_ == lac);
	}
}

void test_location_area_identification::decode_bit_stream_bad_verification()
{
	{
		mobile_country_code_type mcc("F11");
		mobile_network_code_type mnc("26");
		location_area_code_type lac = 55432;
		test_gsm_bit_stream bs;

		bs.test_bit_stream_[0] = 0x1F;
		bs.test_bit_stream_[1] = 0xF1;
		bs.test_bit_stream_[2] = 0x62;
		bs.test_bit_stream_[3] = lac >> 8;
		bs.test_bit_stream_[4] = lac & 0xFF;

	
		location_area_identification lai(value_only_format);
	
		lai.decode(bs);
	
		bool threw_error = false;
		std::string error_str;
		try { lai.verify(); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }

		BOOST_ASSERT(threw_error == true);
		BOOST_ASSERT(error_str == "MCC digit is not a valid binary coded decimal (4 bits).");
	}
	{
		mobile_country_code_type mcc("411");
		mobile_network_code_type mnc("C6");
		location_area_code_type lac = 55432;
		test_gsm_bit_stream bs;

		bs.test_bit_stream_[0] = 0x14;
		bs.test_bit_stream_[1] = 0xF1;
		bs.test_bit_stream_[2] = 0x6C;
		bs.test_bit_stream_[3] = lac >> 8;
		bs.test_bit_stream_[4] = lac & 0xFF;

	
		location_area_identification lai(value_only_format);
	
		lai.decode(bs);
	
		bool threw_error = false;
		std::string error_str;
		try { lai.verify(); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }

		BOOST_ASSERT(threw_error == true);
		BOOST_ASSERT(error_str == "MNC digit is not a valid binary coded decimal (4 bits).");
	}
}