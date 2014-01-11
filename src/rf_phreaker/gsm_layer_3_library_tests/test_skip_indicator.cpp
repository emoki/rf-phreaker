#include "rf_phreaker/gsm_layer_3_library_tests/test_skip_indicator.h"
#include "rf_phreaker/gsm_layer_3_library/skip_indicator.h"

test_skip_indicator::test_skip_indicator(void)
{
}


test_skip_indicator::~test_skip_indicator(void)
{
}

void test_skip_indicator::decode_good_bit_stream()
{
	test_gsm_bit_stream bs1;

	bs1.test_bit_stream_[0] = 0;
	
	skip_indicator skip(value_only_format, true);
	
	skip.decode(bs1);
	
	bool threw_error = false;
	try { skip.verify(); } catch(std::exception err) { threw_error = true; }

	BOOST_ASSERT(threw_error == false);
	BOOST_ASSERT(skip.skip_indicator_ == false);

	// if skip indicator is not zero then message should be skipped.
	bool upper_nibble = true;
	uint32_t bits_consumed = 0;
	int shift_bits = 4;
	for(int i = 0; i < 2; i++)
	{
		for(int i = 1; i < 0x0f; i++)
		{
			test_gsm_bit_stream bs(bits_consumed);

			bs.test_bit_stream_[0] = i << shift_bits;
			
			skip_indicator skip(value_only_format, upper_nibble);
	
			skip.decode(bs);
	
			bool threw_error = false;
			try { skip.verify(); } catch(std::exception err) { threw_error = true; }

			BOOST_ASSERT(threw_error == false);
			BOOST_ASSERT(skip.skip_indicator_ == true);
		}
		upper_nibble = false;
		bits_consumed = 4;
		shift_bits = 0;
	}
}

void test_skip_indicator::decode_bit_stream_bad_verification()
{
}