#include "rf_phreaker/lte_layer_3_decoder_tests/lte_decoding_tests.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include <fstream>
#include <boost/assert.hpp>

void lte_decoding_tests::run_automated_tests()
{
	lte_asn1_decoder decoder;

	std::ifstream file("lte_bitstreams.txt");
	//std::ifstream file("lte_non_working_bitstreams.txt");

	BOOST_ASSERT(file);

	int total_messages = 0;
	int sib1_messages = 0;
	int other_messages = 0;
	
	//std::ofstream tmp("lte_non_working_bitstreams.txt");

	while(file) {
		bit_stream_container_mem bit_stream;
		file >> bit_stream;

		//if(bit_stream.bit_stream()[0] != 0x68)
		//	tmp << bit_stream << "\n";

		layer_3_information::lte_rrc_message_aggregate message;

		decoder.decode_bcch_bch_message(bit_stream.bit_stream(), bit_stream.num_of_bytes(), bit_stream.unused_bits(), message);

		std::cout << message.mcc_.to_string() << "\t"
			<< message.mnc_.to_string() << "\t"
			<< message.lac_ << "\t"
			<< message.cid_ << "\t"
			<< "\n";

		++total_messages;
		if(message.is_cid_decoded())
			++sib1_messages;
		else
			++other_messages;
	}

	std::cout << "\n\ntotal messages: " << total_messages
		<< " sib1 messages: " << sib1_messages
		<< " other_messages: " << other_messages
		<< " sib1/other: " << sib1_messages / other_messages << "%"
		<< "\n";
}