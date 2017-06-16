// test_asn1c_open_source_dll.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <stdint.h>
#include "rf_phreaker/umts_layer_3_decoder_tests/test_segmented_sib.h"
#include "rf_phreaker/umts_layer_3_decoder_tests/test_bit_stream_container.h"
#include "rf_phreaker/umts_layer_3_decoder/umts_layer_3_decoder.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate.h"
#include "rf_phreaker/layer_3_common/umts_bcch_bch_message_aggregate_io.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"

int main(int argc, char* argv[])
{

	test_segmented_sib test_segments;
	test_segments.run_automated_tests();

	test_bit_stream_container bit_stream_container;
	bit_stream_container.run_automated_tests();

	std::ofstream output("test_bit_streams.csv");
	
	BOOST_VERIFY(output.good());

	auto store_description = true;
	umts_asn1_decoder umts_decoder;
	umts_decoder.store_descriptions(store_description);

	std::vector<layer_3_information::pdu_element_type> elements;

	elements.push_back(layer_3_information::pdu_element_type::umts_mib);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib1);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib3);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib4);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11_bis);

	umts_decoder.specify_sibs_for_decoding(&elements.at(0), elements.size());

	std::string base_filename = "../../../../rf_phreaker/test_files/";
	std::ifstream file(base_filename + "umts_bitstreams.txt");

	BOOST_ASSERT(file);


	while(file) {
		layer_3_information::unique_sector_key_type sector_key;
		bit_stream_container_mem bit_stream;
		file >> sector_key;
		file >> bit_stream;

		layer_3_information::umts_bcch_bch_message_aggregate umts_message;
		umts_message.clear();
		umts_message.unique_sector_key_ = sector_key;

		umts_decoder.decode_bcch_bch_message(bit_stream.bit_stream(), bit_stream.num_of_bytes(), bit_stream.unused_bits(), umts_message);

		static std::ofstream file("umts_layer_3.txt");
		std::cout << umts_message << std::endl;
		file << umts_message << std::endl;

		if(store_description) {
			static std::ofstream d_file("umts_layer_3_description.txt");
			auto v = umts_decoder.get_text_description();
			for(auto &i : v) {
				d_file << i << "\n";
				std::cout << i << "\n";
			}
			d_file << std::endl;
		}
	}
}

