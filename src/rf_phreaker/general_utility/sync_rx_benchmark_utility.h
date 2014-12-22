#pragma once

#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/settings.h"

class benchmark_settings {
public:
	int start_buffer_size_;
	int start_num_buffer_;
	int start_num_transfer_;
	int max_num_transfers_;
	int max_buffer_size_;
	int max_num_buffers_;
	int buffer_size_increment_;
	int num_buffer_increment_;
	int num_transfer_increment_;
	std::string filename_;
	rf_phreaker::time_type packet_length_;
	rf_phreaker::frequency_type freq_start_;
	rf_phreaker::frequency_type freq_end_;
	rf_phreaker::frequency_type freq_increment_;
	rf_phreaker::bandwidth_type bandwidth_;
	std::vector<rf_phreaker::frequency_type> sampling_rates_;
};

class sync_rx_benchmark_utility {
public:
	static void benchmark(benchmark_settings &settings) {
		using namespace rf_phreaker::scanner;

		rf_phreaker::blade_settings blade_config;
		blade_config.log_level_ = 2;
		blade_config.rx_sync_buffer_size_ = settings.start_buffer_size_;
		blade_config.rx_sync_num_buffers_ = settings.start_num_buffer_;
		blade_config.rx_sync_num_transfers_ = settings.start_num_transfer_;
		blade_config.rx_sync_timeout_ = 5000;

		blade_rf_controller scanner;
		auto scanner_list = scanner.list_available_scanners();
		// Sometimes the libbladeRF reports there is a connected unit but does not give serial.
		// Requesting the list again seems to fix it.
		if(scanner_list.size() && (*scanner_list.begin())->id() == "")
			scanner_list = scanner.list_available_scanners();

		if(scanner_list.empty()) {
			std::cout << "No scanner found." << std::endl;
		}
		else {
			auto id = (*scanner_list.begin())->id();
			
			std::cout << "Opening scanner " << id << std::endl;

			scanner.open_scanner_and_refresh_scanner_info(id);

			scanner.do_initial_scanner_config(blade_config);

			scanner.set_log_level(blade_config.log_level_);

			std::cout << "Starting benchmark." << std::endl;

			// GPIO must also be set just before collecting inside blade_rf_controller.
			uint32_t gpio;
			scanner.read_config_gpio(gpio);
			gpio |= 0x200;
			scanner.write_config_gpio(gpio);
			
			run_benchmark(settings, scanner, blade_config);
		}
	}

	static void run_benchmark(benchmark_settings &s, rf_phreaker::scanner::blade_rf_controller &scanner, rf_phreaker::blade_settings &initial_config) {
		auto current_config = initial_config;
		for(int buffer_size = initial_config.rx_sync_buffer_size_; buffer_size <= s.max_buffer_size_; buffer_size += s.buffer_size_increment_) {
			current_config.rx_sync_buffer_size_ = buffer_size;

			for(int num_buffers = initial_config.rx_sync_num_buffers_; num_buffers <= s.max_num_buffers_; num_buffers += s.num_buffer_increment_) {
				current_config.rx_sync_num_buffers_ = num_buffers;

				for(int num_xfers = initial_config.rx_sync_num_transfers_; num_xfers < current_config.rx_sync_num_buffers_; num_xfers += s.num_transfer_increment_) {
					if(num_xfers > s.max_num_transfers_)
						break;
					
					current_config.rx_sync_num_transfers_ = num_xfers;

					collect_packets(s, scanner, current_config);
				}
			}
		}
	}

	static void collect_packets(benchmark_settings &s, rf_phreaker::scanner::blade_rf_controller &scanner, rf_phreaker::blade_settings &config) {
		using namespace rf_phreaker;
		using namespace rf_phreaker::scanner;

		scanner.set_blade_sync_rx_settings(config);

		//std::cout << "Buf size: " << config.rx_sync_buffer_size_ << ". Num bufs: " << config.rx_sync_num_buffers_ << ". Num xfers: " << config.rx_sync_num_transfers_ << ".";

		auto throw_away = config.rx_sync_buffer_size_*config.rx_sync_num_buffers_;
		int samples_collected = 0;

		gain_type gain(lms::LNA_MAX, 30, 0);
		for(frequency_type sampling_rate : s.sampling_rates_) {
			drop_info drops; drops.num_drop_locations_ = 0; drops.total_dropped_samples_ = 0;
			int64_t total_ms_elapsed = 0;
			int errors = 0;
			for(frequency_type f = s.freq_start_; f <= s.freq_end_; f += s.freq_increment_) {
				try {
					//std::cout << "Freq: " << f / 1e6 << "\n";
					auto start_time = std::chrono::high_resolution_clock::now();
					auto signal = scanner.get_rf_data(f, s.packet_length_, s.bandwidth_, gain, sampling_rate);
					auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time);
					total_ms_elapsed += time_elapsed.count();
					samples_collected = signal.get_iq().length();
					auto tmp_drop_info = find_num_dropped_sample_locations(scanner.get_internal_iq_buffer(),
						samples_collected, throw_away);
					drops.num_drop_locations_ += tmp_drop_info.num_drop_locations_;
					drops.total_dropped_samples_ += tmp_drop_info.total_dropped_samples_;
				}
				catch(rf_phreaker_error &err) {
					auto str(std::to_string(err.error_type_) + "\t" + std::to_string(err.error_code_) + "\t" + err.what());
					std::cout << str << std::endl;
					static std::ofstream file("sync_rx_benchmark_error_log.txt");
					if(file) file << str << std::endl;
					if(++errors > 10) {
						auto str("Stopping benchmark. Too many errors!");
						if(file) file << str << std::endl;
						std::cout << str << std::endl;
						throw std::runtime_error(str);
					}
					f -= s.freq_increment_;
				}
			}

			output_benchmark(drops, sampling_rate, s, config, total_ms_elapsed, samples_collected, throw_away);
		}
	}

	struct drop_info {
		int num_drop_locations_;
		int64_t total_dropped_samples_;
	};
	static drop_info find_num_dropped_sample_locations(const rf_phreaker::scanner::ipp_16sc_aligned_buffer &buf, int num_samples, int throw_away) {
		auto *iq = (const uint32_t*)(buf.get_aligned_array()) + throw_away;
		drop_info drops; drops.num_drop_locations_ = 0; drops.total_dropped_samples_ = 0;
		auto first = *iq;
		for(int i = 1; i < num_samples; ++i) {
			auto next = *(iq + i);
			if(next - first != 1 && (first != UINT32_MAX)) {
				//std::cout << "drop location: " << i << "\n";
				//std::cout << first << "\t" << next << "\n";
				++drops.num_drop_locations_;
				drops.total_dropped_samples_ += next - first;
			}
			first = next;
		}
		if(0) {
			static int num = 0;
			auto *iq = (const uint16_t*)(buf.get_aligned_array());
			std::ofstream f("debug_packet_" + std::to_string(num++) + ".txt");
			for(int i = 0; i < num_samples; ++i) {
				f << *(iq + i) << "\n";
			}
		}
		return drops;
	}

	static void output_benchmark(drop_info drops, rf_phreaker::frequency_type sampling_rate, benchmark_settings &s, rf_phreaker::blade_settings &config, 
			int64_t time_elapsed, int samples_collected, int samples_ignored) {
		static bool output_header = true;
		static std::ofstream f(s.filename_);
		if(!f)
			throw std::runtime_error("Unable to open benchmark file: " + s.filename_);
		if(output_header) {
			auto str("start_freq\tend_freq\tfreq_increment\tbandwidth\tpacket_length(ms)\t"
				"sampling_rate\tbuffer_size\tnum_buffers\tnum_transfers\ttimeout(ms)\t"
				"time_elapsed(s)\tsamples_collected\tsamples_ignored\tnum_drop_locations\ttotal_samples_dropped\n");
			f << str;
			std::cout << str;
			output_header = false;
		}

		f << s.freq_start_ / 1e6 << "\t"
			<< s.freq_end_ / 1e6 << "\t"
			<< s.freq_increment_ / 1e6 << "\t"
			<< s.bandwidth_ / 1e6 << "\t"
			<< s.packet_length_ / 1e6 << "\t"
			<< sampling_rate / 1e6 << "\t"
			<< config.rx_sync_buffer_size_ << "\t"
			<< config.rx_sync_num_buffers_ << "\t"
			<< config.rx_sync_num_transfers_ << "\t"
			<< config.rx_sync_timeout_ << "\t"
			<< time_elapsed / 1e3 << "\t"
			<< samples_collected << "\t"
			<< samples_ignored << "\t"
			<< drops.num_drop_locations_<< "\t"
			<< drops.total_dropped_samples_ << std::endl;
		std::cout << s.freq_start_ / 1e6 << "\t"
			<< s.freq_end_ / 1e6 << "\t"
			<< s.freq_increment_ / 1e6 << "\t"
			<< s.bandwidth_ / 1e6 << "\t"
			<< s.packet_length_ / 1e6 << "\t"
			<< sampling_rate / 1e6 << "\t"
			<< config.rx_sync_buffer_size_ << "\t"
			<< config.rx_sync_num_buffers_ << "\t"
			<< config.rx_sync_num_transfers_ << "\t"
			<< config.rx_sync_timeout_ << "\t"
			<< time_elapsed / 1e3 << "\t"
			<< samples_collected << "\t"
			<< samples_ignored << "\t"
			<< drops.num_drop_locations_ << "\t"
			<< drops.total_dropped_samples_ << "\n";
	}

};