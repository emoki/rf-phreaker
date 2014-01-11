#pragma once

#include "rf_phreaker\scanner\scanner_controller_interface.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/byte_aligned_buffer.h"
#include "rf_phreaker/scanner/time_samples_conversion.h"
#include "rf_phreaker/scanner/sampling_rate_conversion.h"
#include "rf_phreaker/scanner/rf_switch_conversion.h"
#include "rf_phreaker/scanner/lms_defines.h"
#include "rf_phreaker/scanner/scanner_blade_rf.h"

namespace rf_phreaker {
	namespace scanner {

		class comm_blade_rf;

		class blade_rf_controller
		{
		public:
			blade_rf_controller(comm_type comm = USB_BLADE_RF);

			~blade_rf_controller();

			std::vector<comm_info_ptr> list_available_scanners();

			void open_scanner(const scanner_id_type &id);

			void close_scanner();

			void do_initial_scanner_config();

			void config_scanner_for_collection(std::vector<rf_phreaker::frequency_type> &freqs);

			void update_dds(); // updates values.. does not calculate dds.. that would be done with 

			const scanner* get_scanner();

			const scanner_blade_rf* get_scanner_blade_rf();

			rf_phreaker::gps get_gps_data();

			measurement_info get_rf_data(rf_phreaker::frequency_type freq, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate = 0);

			measurement_info get_rf_data(rf_phreaker::frequency_type freq, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate,
										 int rx_vga_1, int rx_vga_2, lms::lna_gain_enum lna_gain);

		private:
			measurement_info get_rf_data_(rf_phreaker::frequency_type freq, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate = 0);

			void refresh_scanner_info();

			int check_blade_status(int return_status);

			ipp_16sc_aligned_buffer aligned_buffer_;

			sampling_rate_conversion sampling_rate_conversion_;

			time_samples_conversion time_samples_conversion_;

			rf_switch_conversion rf_switch_conversion_;

			std::unique_ptr<comm_blade_rf> comm_blade_rf_;

			std::shared_ptr<scanner_blade_rf> scanner_blade_rf_;
		};

	}
}