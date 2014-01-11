#include "rf_phreaker/gsm_layer_3_library_tests/test_protocol_discriminator.h"
#include "rf_phreaker/gsm_layer_3_library/protocol_discriminator.h"

test_protocol_discriminator::test_protocol_discriminator(void)
{
}


test_protocol_discriminator::~test_protocol_discriminator(void)
{
}
void test_protocol_discriminator::decode_good_bit_stream()
{

	bool upper_nibble = true;
	uint32_t bits_consumed = 0;
	int shift_bits = 4;
	for(int i = 0; i < 2; i++)
	{
		for(int i = 0; i <= (int)test_procedures; i++)
		{
			if(i == 0x0d) continue;
	
			test_gsm_bit_stream bs(bits_consumed);

			bs.test_bit_stream_[0] = i << shift_bits;
	
			protocol_discriminator upper(value_only_format, upper_nibble);
	
			upper.decode(bs);
	
			bool threw_error = false;
			try { upper.verify(); } catch(std::exception err) { threw_error = true; }

			BOOST_ASSERT(threw_error == false);
			BOOST_ASSERT(upper.protocol_discriminator_ == (protocol_discriminator_code)i);
		}
		upper_nibble = false;
		bits_consumed = 4;
		shift_bits = 0;
	}
}

void test_protocol_discriminator::decode_bit_stream_bad_verification()
{
	test_gsm_bit_stream bs;

	bs.test_bit_stream_[0] = 0x0d;
	
	protocol_discriminator proto(value_only_format, false);
	
	proto.decode(bs);
	
	bool threw_error = false;
	std::string error_str;
	try { proto.verify(); } catch(std::exception &err) { threw_error = true; error_str = err.what(); }

	BOOST_ASSERT(threw_error == true);
	BOOST_ASSERT(error_str == "Error verifying protocol_discriminator.");
	BOOST_ASSERT(proto.protocol_discriminator_ == 0x0d);
}
