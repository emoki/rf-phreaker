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
#include "rf_phreaker/layer_3_common/lte_rrc_message_aggregate.h"
#include "rf_phreaker/layer_3_common/pdu_element_types.h"
#include "rf_phreaker/layer_3_common/bcch_bch_message_aggregate.h"

int main(int argc, char* argv[])
{

	test_segmented_sib test_segments;
	test_segments.run_automated_tests();

	test_bit_stream_container bit_stream_container;
	bit_stream_container.run_automated_tests();

	std::ofstream output("test_bit_streams.csv");
	
	BOOST_VERIFY(output.good());

	//lte_asn1_decoder lte_decoder;
	//layer_3_information::lte_rrc_message_aggregate lte_message;
	//lte_message.clear();
	//lte_decoder.decode_bcch_bch_message(lte_sib_1_bit_stream, 22, 0, lte_message);
	//output << 
	//	lte_message.mcc_.num_characters() << "|" << 
	//	lte_message.mcc_.to_string() << "," << 
	//	lte_message.mnc_.num_characters() << "|" << 
	//	lte_message.mnc_.to_string() << "," << 
	//	lte_message.lac_ << "," << 
	//	lte_message.cid_ << "," << 
	//	lte_message.unique_sector_key_ << std::endl;


	umts_asn1_decoder umts_decoder;

	std::vector<layer_3_information::pdu_element_type> elements;

	elements.push_back(layer_3_information::pdu_element_type::umts_mib);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib1);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib3);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib4);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11_bis);

	umts_decoder.specify_sibs_for_decoding(&elements.at(0), elements.size());

	std::string input_dir("E:\\werk\\tno\\software_projects\\asn_decoder\\asn1c_open_source_dll\\test_data\\");
	//std::string input_dir("C:\\Users\\tno\\Documents\\WindFiles\\wider_testing\\sib_11_and_sib_11_bis\\data_for_sib_11\\");
	//std::string input_dir("C:\\tno\\wind3g_trunk\\asn_decoder\\asn1c_open_source_dll\\test_data\\");	

	//std::string input_dir("C:\\cappeen\\beagle_dev\\Debug\\");	
	//std::string input_dir("C:\\Users\\tno\\Documents\\WindFiles\\wider_testing\\v2.11.4.1\\test_segments\\");	
	//std::string input_dir("C:\\Users\\tno\\Documents\\WindFiles\\wider_testing\\v2.11.4.1\\bit_stream_data\\");	
	//std::string filename("wcmda_bit_stream_with_cellid.per");
	//std::string filename("wcmda_bit_stream_test_access_violation_cobham_2100");
	std::string filename("wcmda_bit_stream_1409024166_");
	
	for(int i = 0; i <= 104; i++)
	{
		std::string current_file(input_dir);
		
		current_file.append(filename).append(boost::lexical_cast<std::string>(i)).append(".bin");
	
		std::ifstream file(current_file, std::ios_base::binary);
	
		BOOST_VERIFY(file.good());

		layer_3_information::umts_bcch_bch_message_aggregate umts_message;
		umts_message.clear();

		uint8_t buf[272];
		memset(buf, 0, 272);
		file.read((char*)&umts_message.unique_sector_key_, 4);
		file.read((char*)buf, 272);

		umts_decoder.decode_bcch_bch_message(buf, 34, 4, umts_message);

		output << 
			umts_message.system_frame_number_ << "," << 
			umts_message.mcc_.num_characters() << "|" << 
			umts_message.mcc_.to_string() << "," << 
			umts_message.mnc_.num_characters() << "|" << 
			umts_message.mnc_.to_string() << "," << 
			umts_message.lac_ << "," << 
			umts_message.cid_ << "," << 
			umts_message.unique_sector_key_ << std::endl;

		std::cout <<
			umts_message.system_frame_number_ << "," << 
			umts_message.mcc_.num_characters() << "|" << 
			umts_message.mcc_.to_string() << "," << 
			umts_message.mnc_.num_characters() << "|" << 
			umts_message.mnc_.to_string() << "," << 
			umts_message.lac_ << "," << 
			umts_message.cid_ << "," << 
			umts_message.unique_sector_key_ << std::endl;
	}

	system("Pause");
}

