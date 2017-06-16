// test_gsm_layer_3_decoder.cpp : Defines the entry point for the console application.
//

#include <stdint.h>
#include <fstream>
#include <string>
#include <boost/assert.hpp>
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate.h"
#include "rf_phreaker/layer_3_common/gsm_layer_3_message_aggregate_io.h"
#include "rf_phreaker/gsm_layer_3_decoder/gsm_layer_3_decoder.h"
#include "rf_phreaker/gsm_layer_3_library/gsm_bit_stream.h"

// 49061B2B97130062CC17C8000A59604479800080208043
const uint8_t valid_bit_stream_1[] = { 0x49, 0x06, 0x1B, 0x2B, 0x97, 0x13, 0x00, 0x62, 0xCC, 0x17, 0xC8, 0x00, 0x0A, 0x59, 0x60, 0x44, 0x79, 0x80, 0x00, 0x80, 0x20, 0x80, 0x43 };

//49061B376C1300627D66C8000A59604479000080208043
const uint8_t valid_bit_stream_2[] = { 0x49, 0x06, 0x1B, 0x37, 0x6C, 0x13, 0x00, 0x62, 0x7D, 0x66, 0xC8, 0x00, 0x0A, 0x59, 0x60, 0x44, 0x79, 0x00, 0x00, 0x80, 0x20, 0x80, 0x43 };

const uint8_t invalid_bit_stream_1[] = { 0x55, 0x06, 0x19, 0x8F, 0x19, 0xA0, 0x00, 0x40, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79, 0x80, 0x00, 0x6B };

int main(int argc, char* argv[])
{
	// We are using a relative path to load the test files.  It follows the convention of a out-of-source build using cmake.  
	// The build directory is located on the same level as the git root directory.  The git root directory's name is lte_phreaker
	// and the test_files are located within test_files. So the directory struct would look like:
	// ./cmake_build_directory			(cmake build directory)
	// ./lte_phreaker					(git root directory)
	// ./lte_phreaker/test_files		(directory containing test data)
	std::string folder_path =
		"../../../../rf_phreaker/test_files/cobham10/"
		//"../../../../rf_phreaker/test_files/"
		;

	std::string prefix =
		"gsm_bit_streams3"
		//"gsm_bit_streams"
		;

	std::string suffix =
		//".bin";
		".txt";

	auto store_description = true;
	gsm_layer_3_decoder decoder;

	decoder.store_descriptions(store_description);
	
	auto filename = folder_path + prefix + suffix;
	std::ifstream f(filename.c_str());

	for(auto i = 0; i < 10000; ++i) {
		gsm_bit_stream_mem stream;
		f >> stream;
		if(!f)
			break;

		layer_3_information::gsm_layer_3_message_aggregate message;
		auto status = decoder.decode_bcch_message(stream.bit_stream(), stream.num_bytes_in_bit_stream(), stream.num_bits_unused_in_bit_stream(), message);

		BOOST_ASSERT(status == 0);
		
		static std::ofstream out("gsm_layer_3.txt");
		static auto out_header = false;
		if(!out_header) {
			out << "index\t";
			layer_3_information::header(out, message) << std::endl;
			out_header = true;
		}
		out << i << "\t" << message << std::endl;

		if(store_description) {
			static std::ofstream description_file("gsm_decoded_sibs_discription.txt");
			auto d = decoder.get_text_description();
			for(auto &k : d)
				description_file << k << "\n";
			description_file << std::endl;
		}
	}
	
	layer_3_information::gsm_layer_3_message_aggregate message;
	int32_t status = decoder.decode_bcch_message(valid_bit_stream_1, 23, 0, message);
	BOOST_ASSERT(status == 0);

	status = decoder.decode_bcch_message(valid_bit_stream_2, 23, 0, message);
	BOOST_ASSERT(status == 0);

	decoder.decode_bcch_message(invalid_bit_stream_1, 23, 0, message);
	BOOST_ASSERT(status == 0);



	return 0;
}

