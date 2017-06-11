#include "rf_phreaker/lte_layer_3_decoder_tests/lte_decoding_tests.h"
#include "rf_phreaker/lte_layer_3_decoder/lte_layer_3_decoder.h"
#include "rf_phreaker/layer_3_decoder_common/bit_stream_container.h"
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate_io.h"
#include <fstream>
#include <boost/assert.hpp>

void lte_decoding_tests::run_automated_tests()
{
	auto store_description = true;
	lte_asn1_decoder decoder;
	decoder.store_text_description(store_description);

	std::string base_filename = "../../../../rf_phreaker/test_files/";
	std::ifstream file(base_filename + "lte_bitstreams_sib6.txt");
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

		
		++total_messages;
		if(message.is_cid_decoded())
			++sib1_messages;
		else
			++other_messages;

		static std::ofstream output_file("lte_decoded_sibs.txt");
		static bool write_header = true;
		if(write_header) {
			output_file << "file_num\n";
			write_header = false;
		}
		output_file << total_messages << "\t" << message << "\n";
		std::cout << total_messages << "\t" << message << "\n";

		if(store_description) {
			static std::ofstream description_file("lte_decoded_sibs_discription.txt");
			auto d = decoder.get_text_description();
			for(auto &k : d)
				description_file << k << "\n";
			description_file << std::endl;
		}
	}

	std::cout << "\n\ntotal messages: " << total_messages
		<< " sib1 messages: " << sib1_messages
		<< " other_messages: " << other_messages
		<< " sib1/other: " << sib1_messages / other_messages << "%"
		<< "\n";
}