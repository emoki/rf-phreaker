#pragma once

#include "rf_phreaker/scanner/scanner_controller_interface.h"
#include "rf_phreaker/common/common_types.h"
#include "rf_phreaker/common/concurrent.h"
#include "rf_phreaker/common/measurements.h"
#include "rf_phreaker/scanner/scanner_comm.h"
#include "rf_phreaker/scanner/frequency_v_tune.h"
#include "rf_phreaker/scanner/measurement_info.h"
#include "rf_phreaker/scanner/byte_aligned_buffer.h"
#include "rf_phreaker/scanner/time_samples_conversion.h"
#include "rf_phreaker/scanner/sampling_rate_conversion.h"
#include "rf_phreaker/scanner/rf_switch_conversion.h"

namespace rf_phreaker { namespace scanner {

/** 
Handles the communication to one scanner.
Includes: 
- determination of scanner comm type
- scanner initialization
- packet collection
*/

class scanner_controller : public scanner_controller_interface
{
public:
	scanner_controller(comm_type comm = AUTO);

	~scanner_controller(void);

	scanner_controller(scanner_controller& other);

	std::future<std::vector<comm_info_ptr>> list_available_scanners();

	void open_scanner(const scanner_id_type &id);

	void close_scanner();

	void do_initial_scanner_config();

	//void background_config();  ??

	void config_scanner_for_collection(std::vector<rf_phreaker::frequency_type> &freqs);

	void update_dds(); // updates values.. does not calculate dds.. that would be done with 

	void get_scanner_info();

	std::future<rf_phreaker::gps> get_gps_data();

	std::future<measurement_info> get_rf_data(rf_phreaker::frequency_type freq, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate = 0);

private:

	struct sc_data
	{
		sc_data(comm_type comm);

		sc_data(sc_data &&sc);

		sc_data& operator=(const sc_data a);

		scanner_comm& scanner_comm() { return *scanner_comm_ptr_.get(); }

		scanner_comm_ptr scanner_comm_ptr_;

		frequency_v_tune frequency_v_tune_;

		ipp_16sc_aligned_buffer aligned_buffer_;

		sampling_rate_conversion sampling_rate_conversion_;

		time_samples_conversion time_samples_conversion_;

		rf_switch_conversion rf_switch_conversion_;

	private:
		sc_data(const sc_data &) {};
	};
	concurrent<sc_data> sc_data_;
};

}}