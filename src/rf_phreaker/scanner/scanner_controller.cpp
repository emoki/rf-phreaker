#include "rf_phreaker/scanner/scanner_controller.h"
#include "rf_phreaker/scanner/scanner_comm_usb.h"
#include "rf_phreaker/scanner/scanner_initialization.h"
#include "rf_phreaker/scanner/gain.h"
#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/frequency_v_tune.h"
#include "rf_phreaker/scanner/sampling_rate_conversion.h"

#include <boost/timer/timer.hpp>

//using namespace rf_phreaker;
using namespace rf_phreaker::scanner;

scanner_controller::sc_data::sc_data(comm_type comm)
	: scanner_comm_ptr_(new scanner_comm_usb(comm))
{}

scanner_controller::sc_data::sc_data(sc_data &&sc)
	: scanner_comm_ptr_(std::move(sc.scanner_comm_ptr_))
	, frequency_v_tune_(std::move(sc.frequency_v_tune_))
	, aligned_buffer_(std::move(sc.aligned_buffer_))
{}

scanner_controller::sc_data& scanner_controller::sc_data::operator=(const sc_data a)
{
	sc_data tmp(a); 
	std::swap(tmp, *this);
	return *this;
}



scanner_controller::scanner_controller(comm_type comm)
	: sc_data_(comm == AUTO ? USB_FTDI_DEVICE : comm)
{
}


scanner_controller::~scanner_controller(void)
{
	sc_data_([=] (sc_data &sc) 
	{
		if(sc.scanner_comm_ptr_->is_scanner_open())
			sc.scanner_comm().close_scanner();
	});
}

std::future<std::vector<comm_info_ptr>> scanner_controller::list_available_scanners()
{
	return sc_data_([=] (sc_data &sc) 
	{
		return sc.scanner_comm_ptr_->list_scanners();
	});
}

void scanner_controller::open_scanner(const scanner_id_type &id)
{
	sc_data_([=] (sc_data &sc) 
	{
		sc.scanner_comm_ptr_->open_scanner(id);
	});
}

void scanner_controller::close_scanner()
{
	sc_data_([=] (sc_data &sc) 
	{
		sc.scanner_comm_ptr_->close_scanner();
	});
}

void scanner_controller::do_initial_scanner_config()
{
	sc_data_([=] (sc_data &sc) 
	{
		// send default parameters to lime
		// construction of licensing
		// construction of calibration table

		scanner_initialization scanner_init;

		scanner_init.initialize_scanner(sc.scanner_comm());
	});

}

void scanner_controller::config_scanner_for_collection(std::vector<rf_phreaker::frequency_type> &freqs)
{
	freqs;
	// Check band licensing
	// find initial gain values
	// handle vtune on all freqs we will be collecting
}

void scanner_controller::update_dds()
{
}

void scanner_controller::get_scanner_info()
{
}

std::future<rf_phreaker::gps> scanner_controller::get_gps_data()
{
	return sc_data_([=] (sc_data &)
	{
		return rf_phreaker::gps();
	});
}

std::future<measurement_info> scanner_controller::get_rf_data(rf_phreaker::frequency_type frequency, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate)
{
	return sc_data_([=] (sc_data &sc) 
	{
		// determine gain
		// set freq packets
		// set bandwidth
		// set decimation 
		// set rf switchs
		// set samples packet

		rf_phreaker::frequency_type actual_sampling_rate_used = sampling_rate > 0 ?
			sc.sampling_rate_conversion_.find_lower_bound_sampling_rate(sampling_rate) :
			sc.sampling_rate_conversion_.find_lower_bound_sampling_rate(bandwidth);
		
		packet_container container;

		container.add_packet(std::make_shared<set_decimation_packet>(sc.sampling_rate_conversion_.find_decimation_value(actual_sampling_rate_used)));
	
		container.add_container(sc.frequency_v_tune_.convert_freq_and_determine_vtune(sc.scanner_comm(), frequency));

		container.add_container(gain::get_default_gain(frequency));

		container.add_container(bandwidth_conversion::get_bandwidth_and_enable_lpf(bandwidth));


		container.add_container(sc.rf_switch_conversion_.get_rf_switches(frequency)); 

		int num_samples = sc.time_samples_conversion_.convert_to_samples(time_ms, actual_sampling_rate_used);

		auto samples_go_packet = std::make_shared<set_sample_size_and_go_packet>(num_samples);

		container.add_packet(samples_go_packet);


		auto return_bytes = container.return_bytes_expected();

		sc.aligned_buffer_.align_array(return_bytes);


		sc.scanner_comm_ptr_->transfer_packet_container(container, sc.aligned_buffer_.get_aligned_array());
		

		//sc.aligned_buffer_.get_unaligned_array().output_binary("output_raw.bin");
		//sc.aligned_buffer_.get_unaligned_array().output_text("output_raw.txt");

		measurement_info data(num_samples, 
			frequency, 
			bandwidth_conversion::convert_to_bandwidth_type(bandwidth_conversion::find_lower_bound_bandwidth(bandwidth)), 
			actual_sampling_rate_used,
			time_ms);


		// 2 * length because we're dealing with complex numbers!
		ipp_helper::check_status(ippsSwapBytes_16u_I((Ipp16u*)&(*samples_go_packet->get_iq()), num_samples * 2));
		sc.aligned_buffer_.get_unaligned_array().output_binary("output_raw_swapped.bin");
		
		ipp_helper::check_status(ippsConvert_16s32f((Ipp16s*)&(*samples_go_packet->get_iq()), (Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

		//data.get_iq().output_binary("output_formatted.bin");
		//data.get_iq().output_text("output_formatted.txt");

		return data;
	});
}