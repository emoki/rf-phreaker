#include "stdafx.h"
#include <boost/program_options.hpp>
#include "rf_phreaker/general_utility/calibration_utility.h"
#include "rf_phreaker/general_utility/sync_rx_benchmark_utility.h"
#include "rf_phreaker/general_utility/scanner_stress_test.h"

int handle_calibration(int argc, char* argv[]) {
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

int handle_sync_rx_benchmark(int argc, char* argv[]) {
	namespace po = boost::program_options;
	using namespace rf_phreaker;
	try {
		// Option variables.
		benchmark_settings settings;
		std::vector<frequency_type> default_sampling_rates;
		default_sampling_rates.push_back(khz(1920));
		default_sampling_rates.push_back(khz(3840));
		default_sampling_rates.push_back(khz(4875));
		default_sampling_rates.push_back(khz(7680));
		default_sampling_rates.push_back(khz(15360));
		default_sampling_rates.push_back(khz(23040));
		default_sampling_rates.push_back(khz(30720));

		po::options_description desc("Allowed options");

		desc.add_options()
			("help,h", "Produce help message.")
			("start_buffer_size", po::value<int>(&settings.start_buffer_size_)->default_value(20 * 1024), "Buffer size to start benchmark")
			("start_num_buffer", po::value<int>(&settings.start_num_buffer_)->default_value(248), "Number of buffers to start benchmark")
			("start_num_transfer", po::value<int>(&settings.start_num_transfer_)->default_value(64), "Number of transfers to start benchmark")

			("max_buffer_size,b", po::value<int>(&settings.max_buffer_size_)->default_value(1024 * 64), "Maximum buffer size to use.")
			("max_num_buffers,n", po::value<int>(&settings.max_num_buffers_)->default_value(1024), "Maximum number of buffers to use")
			("max_num_transfers,x", po::value<int>(&settings.max_num_transfers_)->default_value(1023), "Maximum number of transfers to use.\n")

			("buffer_size_increment", po::value<int>(&settings.buffer_size_increment_)->default_value(2 * 1024), "Buffer size increment")
			("num_buffer_increment", po::value<int>(&settings.num_buffer_increment_)->default_value(4), "Number of buffers increment")
			("num_transfer_increment", po::value<int>(&settings.num_transfer_increment_)->default_value(4), "Number of transfers increment")

			("filename,f", po::value<std::string>(&settings.filename_)->default_value("sync_rx_benchmark.txt"), "Output filename")
			("sampling_rates,s", po::value<std::vector<frequency_type>>(&settings.sampling_rates_)->multitoken(),
			"Sampling rates hz to use")
			("start_freq", po::value<frequency_type>(&settings.freq_start_)->default_value(mhz(1930)), "Frequency hz to start benchmark")
			("end_freq", po::value<frequency_type>(&settings.freq_end_)->default_value(mhz(1990)), "Frequency hz to end benchmark")
			("freq_increment", po::value<frequency_type>(&settings.freq_increment_)->default_value(mhz(1)), "Frequency hz increment")
			("packet_length,p", po::value<time_type>(&settings.packet_length_)->default_value(60), "Collection packet length in ms")
			("bandwidth,w", po::value<bandwidth_type>(&settings.bandwidth_)->default_value(mhz(2)), "Bandwidth hz");

		// Read command line.
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		if(vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}
		vm.notify();

		if(settings.sampling_rates_.empty())
			settings.sampling_rates_ = default_sampling_rates;
		for(auto rate : settings.sampling_rates_) {
			if(rate < khz(1920) || rate > khz(30720))
				throw std::runtime_error("sampling_rates must be between 1.92mhz and 30.72mhz");
		}

		if(settings.start_buffer_size_ % 1024 != 0)
			throw std::runtime_error("start_buffer_size must be a multiple of 1024.");
		if(settings.start_num_transfer_ <= 0)
			throw std::runtime_error("start_num_transfer must be positive.");
		if(settings.start_num_buffer_ <= 0)
			throw std::runtime_error("start_num_buffer must be positive.");

		if(settings.max_buffer_size_ % 1024 != 0)
			throw std::runtime_error("max_buffer_size must be a multiple of 1024.");
		if(settings.max_num_buffers_ < 2 || settings.max_num_buffers_ > 4 * 1024)
			throw std::runtime_error("max_num_buffers must be 2 <= x <= 64.");
		if(settings.max_num_transfers_ < 1 || settings.max_num_transfers_ > 4 * 1024 - 1)
			throw std::runtime_error("max_num_transfers be 1 <= x <= 63.");
		if(settings.max_num_transfers_ >= settings.max_num_buffers_)
			throw std::runtime_error("max_num_transfers must be less than max_num_buffers.");

		if(settings.buffer_size_increment_ % 1024 != 0)
			throw std::runtime_error("buffer_size_increment must be a multiple of 1024.");
		if(settings.num_transfer_increment_ <= 0)
			throw std::runtime_error("num_transfer_increment must be positive.");
		if(settings.num_buffer_increment_ <= 0)
			throw std::runtime_error("num_buffer_increment must be positive.");

		if(settings.freq_increment_ < 0)
			throw std::runtime_error("freq_increment must be greater than 0.");
		if(settings.freq_start_ < mhz(500) || settings.freq_start_ > mhz(2600))
			throw std::runtime_error("start_freq must be 500mhz <= x <= 2600mhz.");
		if(settings.freq_end_ < mhz(500) || settings.freq_end_ > mhz(2600))
			throw std::runtime_error("end_freq must be 500mhz <= x <= 2600mhz.");
		if(settings.freq_start_ >= settings.freq_end_)
			throw std::runtime_error("start_freq must be less than end_freq.");
		if(settings.bandwidth_ < mhz(1) || settings.bandwidth_ > mhz(20))
			throw std::runtime_error("bandwidth must be 1mhz <= x <= 20mhz.");
		if(settings.packet_length_ < 5 || settings.packet_length_ > 130)
			throw std::runtime_error("time must be 5ms <= x <= 130ms.");

		settings.packet_length_ = milli_to_nano(settings.packet_length_);

		sync_rx_benchmark_utility::benchmark(settings);
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

int handle_scanner_stress_test(int argc, char* argv[]) {
	namespace po = boost::program_options;

	try {
		// Option variables.
		std::vector<int64_t> snapshots;
		rf_phreaker::stress_test_settings settings;

		po::options_description desc("Allowed options");

		desc.add_options()
			("help,h", "Produce help message.")
			("test_duration,t", po::value<int>(&settings.duration_mins_)->default_value(10), "Test duration (minutes)")
			("snapshots,s", po::value<std::vector<int64_t>>(&snapshots)->multitoken(), "start_freq_hz end_freq_hz freq_increment_hz sampling_rate_hz bandwidth_hz time_nanoseconds.... repeating\n")
			("update_vctcxo,u", po::value<int>(&settings.update_vctcx_trim_duration_s_)->default_value(50), "Update VCTCXO interval (seconds)\n")
			("write_vctcxo,w", po::value<int>(&settings.write_vctcx_trim_duration_s_)->default_value(60), "Write VCTCXO interval (seconds)\n")
			("get_gps_message,g", po::value<int>(&settings.get_gps_message_duration_s_)->default_value(1), "Get GPS message interval (seconds)\n")
			("1pps_cali,c", po::value<int>(&settings.perform_1pps_calibration_s_)->default_value(25), "Perform 1PPS calibration interval (seconds)\n")
			("read_eeprom,r", po::value<int>(&settings.read_eeprom_duration_s_)->default_value(64), "Read EEPROM interval (seconds)\n")
			("log_level,l", po::value<int>(&settings.log_level_)->default_value(0), "Log level.  0 - 5 with 0 being the most verbose\n");

		// Read command line.
		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		if(vm.count("help")) {
			std::cout << desc << std::endl;
			return 1;
		}
		vm.notify();

		if(snapshots.empty() || snapshots.size() % 6 != 0) {
			throw std::exception("Wrong number of parameters for snapshots.  Please input all the necessary parameters: start_freq_hz end_freq_hz freq_increment_hz sampling_rate_hz bandwidth_hz time_nanoseconds");
		}
			 
		for(size_t i = 0; i < snapshots.size();) {
			rf_phreaker::snapshot_setting snap;
			snap.start_freq_ = snapshots[i++];
			snap.end_freq_ = snapshots[i++];
			snap.freq_increment_ = snapshots[i++];
			snap.sampling_rate_ = snapshots[i++];
			snap.bandwidth_ = (rf_phreaker::bandwidth_type)snapshots[i++];
			snap.time_ = snapshots[i++];
			settings.snapshots_.push_back(snap);
		}

		rf_phreaker::scanner_stress_test::run(settings);
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

int main(int argc, char* argv[]) {
	//-c 77ecda454d25738ee419f6fd676170d5 13cadd7137a3ef4d18dcfcc179667998 47d54d57db30c9169c98c53e30c08d9a d01d12c0dc5c71c8a081e0c25f27b6fd d7db1c90fd06a5a6d950615ea7fa6164
	//int status = handle_calibration(argc, argv);
	//int status = handle_sync_rx_benchmark(argc, argv);
	int status = handle_scanner_stress_test(argc, argv);
	system("pause");
	return status;
}

