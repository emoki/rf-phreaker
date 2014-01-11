#include "rf_phreaker/gsm_layer_3_library_tests/test_cell_identity.h"
#include "rf_phreaker/gsm_layer_3_library/cell_identity.h"

test_cell_identity::test_cell_identity(void)
{
}


test_cell_identity::~test_cell_identity(void)
{
}

void test_cell_identity::decode_good_bit_stream()
{
	test_gsm_bit_stream bs;

	cell_identity_type test_cid = 35433; 

	bs.test_bit_stream_[0] = test_cid >> 8;

	bs.test_bit_stream_[1] |= test_cid;
	
	cell_identity cid(value_only_format);
	
	cid.decode(bs);
	
	bool threw_error = false;
	try { cid.verify(); } catch(std::exception err) { threw_error = true; }

	BOOST_ASSERT(threw_error == false);
	BOOST_ASSERT(cid.cell_identity_ == test_cid);
}

void test_cell_identity::decode_bit_stream_bad_verification()
{
}