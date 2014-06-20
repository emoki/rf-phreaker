#include "stdafx.h"
#include <boost/program_options.hpp>
#include "rf_phreaker/general_utility/calibration_utility.h"


int main(int argc, char* argv[]) {
	namespace po = boost::program_options;

	try {
		// Option variables.
		std::vector<std::string> serials;

		po::options_description desc("Allowed options");

		desc.add_options()
			("help,h", "Produce help message.")
			("upload_calibration,c", po::value<std::vector<std::string>>(&serials)->multitoken(),
			"Uploads a calibration file to a scanner.\n"
			"Calibration filename format:\n"
			"13cadd7137a3ef4d18dcfcc179667998_cali.bin."
			"\nExample usage:\n"
			"'-c 13cadd7137a3ef4d18dcfcc179667998'"
			);

		// Read command line.
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		if(vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}
		vm.notify();

		calibration_utility::load_calibrations(serials);


		//auto tmp1 = calibration_utility::read_calibration_from_file("13cadd7137a3ef4d18dcfcc179667998_cali.bin");
		//auto tmp2 = calibration_utility::read_calibration_from_file("47d54d57db30c9169c98c53e30c08d9a_cali.bin");
		//auto tmp3 = calibration_utility::read_calibration_from_file("d01d12c0dc5c71c8a081e0c25f27b6fd_cali.bin");
		//auto tmp4 = calibration_utility::read_calibration_from_file("d7db1c90fd06a5a6d950615ea7fa6164_cali.bin");
		//auto tmp5 = calibration_utility::read_calibration_from_file("77ecda454d25738ee419f6fd676170d5_cali.bin");


		//std::string base = "../../../../rf_phreaker/test_files/calibration_files/";

		//calibration_utility::read_calibration_and_output(base + "Nuand_Board_13cadd7137a3ef4d18dcfcc179667998_140605.txt", base + "RF_Board_13cadd7137a3ef4d18dcfcc179667998_140605.txt",
		//	base + "RF_Switch_13cadd7137a3ef4d18dcfcc179667998_140605.txt");

		//calibration_utility::read_calibration_and_output(base + "Nuand_Board_47d54d57db30c9169c98c53e30c08d9a_140605.txt", base + "RF_Board_47d54d57db30c9169c98c53e30c08d9a_140605.txt",
		//	base + "RF_Switch_47d54d57db30c9169c98c53e30c08d9a_140605.txt");

		//calibration_utility::read_calibration_and_output(base + "Nuand_Board_d01d12c0dc5c71c8a081e0c25f27b6fd_140605.txt", base + "RF_Board_d01d12c0dc5c71c8a081e0c25f27b6fd_140605.txt",
		//	base + "RF_Switch_d01d12c0dc5c71c8a081e0c25f27b6fd_140605.txt");

		//calibration_utility::read_calibration_and_output(base + "Nuand_Board_d7db1c90fd06a5a6d950615ea7fa6164_140605.txt", base + "RF_Board_d7db1c90fd06a5a6d950615ea7fa6164_140605.txt",
		//	base + "RF_Switch_d7db1c90fd06a5a6d950615ea7fa6164_140605.txt");
	}
	catch(std::exception &err) {
		std::cout << "Error: " << err.what() << std::endl;
	}
	catch(...) {
		std::cout << "Unknown error has occurred." << std::endl;
	}
	
	std::cout << std::endl;
	return 0;
}

