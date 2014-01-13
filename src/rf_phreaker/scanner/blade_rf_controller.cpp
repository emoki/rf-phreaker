#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/scanner/comm_blade_rf.h"
#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/lms_utilities.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/scanner_blade_rf_impl.h"
#include "libbladeRF.h"

using namespace rf_phreaker::scanner;


blade_rf_controller::blade_rf_controller(comm_type)
{}

blade_rf_controller::~blade_rf_controller()
{
	if(comm_blade_rf_.get())
		close_scanner();
}

std::vector<comm_info_ptr> blade_rf_controller::list_available_scanners()
{
	std::vector<comm_info_ptr> devices;
	bladerf_devinfo *dev_info;

	int num_devices = bladerf_get_device_list(&dev_info);

	check_blade_status(num_devices);

	for(int i = 0; i < num_devices; i++) {
		devices.push_back(comm_info_ptr(new comm_blade_rf(dev_info[i])));
	}

	bladerf_free_device_list(dev_info);

	return devices;
}

void blade_rf_controller::open_scanner(const scanner_id_type &id)
{
	std::string open_str = "libusb:serial=" + id;

	bladerf *blade_rf;

	check_blade_status(bladerf_open(&blade_rf, open_str.c_str()));

	bladerf_devinfo dev_info;

	check_blade_status(bladerf_get_devinfo(blade_rf, &dev_info));

	comm_blade_rf_.reset(new comm_blade_rf(dev_info, blade_rf));

	// Reset LMS.
	check_blade_status(bladerf_lms_write(comm_blade_rf_->blade_rf(), 0x05, 0x12));
	check_blade_status(bladerf_lms_write(comm_blade_rf_->blade_rf(), 0x05, 0x32));

	refresh_scanner_info();
}

void blade_rf_controller::close_scanner()
{
	bladerf_close(comm_blade_rf_->blade_rf());
	comm_blade_rf_.reset();
}

void blade_rf_controller::do_initial_scanner_config()
{
	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		true));
	
	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_TX,
		false));

	check_blade_status(bladerf_calibrate_dc(comm_blade_rf_->blade_rf(), 
		BLADERF_DC_CAL_LPF_TUNING));

	check_blade_status(bladerf_calibrate_dc(comm_blade_rf_->blade_rf(), 
		BLADERF_DC_CAL_RX_LPF));

	check_blade_status(bladerf_calibrate_dc(comm_blade_rf_->blade_rf(), 
		BLADERF_DC_CAL_RXVGA2));

	check_blade_status(bladerf_set_sampling(comm_blade_rf_->blade_rf(),
		bladerf_sampling::BLADERF_SAMPLING_INTERNAL));

	//bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_VERBOSE);

	// construction of licensing
	// construction of calibration table

}

void blade_rf_controller::config_scanner_for_collection(std::vector<rf_phreaker::frequency_type> &)
{
	// Currently vtune value is calculated on the fly.

	// Check band licensing
	// find initial gain values
	// handle vtune on all freqs we will be collecting
}

void blade_rf_controller::update_dds()
{}

const scanner* blade_rf_controller::get_scanner()
{
	refresh_scanner_info();

	return scanner_blade_rf_.get();
}

const scanner_blade_rf* blade_rf_controller::get_scanner_blade_rf()
{
	refresh_scanner_info();

	return scanner_blade_rf_.get();
}

void blade_rf_controller::refresh_scanner_info()
{
	scanner_blade_rf_impl blade;

	auto comm_blade = comm_blade_rf_->blade_rf();

	check_blade_status(bladerf_get_devinfo(comm_blade, &blade.dev_info_));

	blade.usb_speed_ = static_cast<bladerf_dev_speed>(check_blade_status(bladerf_device_speed(comm_blade_rf_->blade_rf())));

	// bladerf_stats is not currently supported.  FPGA needs to support behavior.
	//check_blade_status(bladerf_stats(comm_blade, &blade.stats_));
	blade.stats_.rx_overruns = 0;
	blade.stats_.rx_throughput = 0;
	blade.stats_.tx_throughput = 0;
	blade.stats_.tx_underruns = 0;

	bladerf_version(&blade.blade_rf_version_);

	check_blade_status(bladerf_fw_version(comm_blade, &blade.firmware_version_));

	check_blade_status(bladerf_fpga_version(comm_blade, &blade.fpga_version_));

	check_blade_status(bladerf_get_vctcxo_trim(comm_blade, &blade.vctcxo_trim_));

	scanner_blade_rf_ = std::make_shared<scanner_blade_rf>(blade);
}

rf_phreaker::gps blade_rf_controller::get_gps_data()
{
	return rf_phreaker::gps();
}

measurement_info blade_rf_controller::get_rf_data(rf_phreaker::frequency_type frequency, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate)
{
	// TODO - Set gain automatically.
	return get_rf_data_(frequency, time_ms, bandwidth, sampling_rate);
}

measurement_info blade_rf_controller::get_rf_data(rf_phreaker::frequency_type frequency, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate,
												  int rx_vga_1, int rx_vga_2, lms::lna_gain_enum lna_gain)
{
	check_blade_status(bladerf_set_lna_gain(comm_blade_rf_->blade_rf(), convert(lna_gain)));

	check_blade_status(bladerf_set_rxvga1(comm_blade_rf_->blade_rf(), rx_vga_1));

	check_blade_status(bladerf_set_rxvga2(comm_blade_rf_->blade_rf(), rx_vga_2));

	return get_rf_data_(frequency, time_ms, bandwidth, sampling_rate);
}

measurement_info blade_rf_controller::get_rf_data_(rf_phreaker::frequency_type frequency, int time_ms, rf_phreaker::bandwidth_type bandwidth, rf_phreaker::frequency_type sampling_rate)
{
	// Do we need to allow access to lpf_mode?

	rf_phreaker::frequency_type actual_sampling_rate_used = sampling_rate > 0 ?
		sampling_rate_conversion_.find_lower_bound_sampling_rate(sampling_rate) :
		sampling_rate_conversion_.find_lower_bound_sampling_rate(bandwidth);

	unsigned int blade_sampling_rate = 0;

	check_blade_status(bladerf_set_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
							actual_sampling_rate_used, &blade_sampling_rate));

	assert(actual_sampling_rate_used == blade_sampling_rate);

	unsigned int blade_bandwidth = 0;

	check_blade_status(bladerf_set_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		bandwidth, &blade_bandwidth));

	check_blade_status(bladerf_select_band(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		frequency));

	check_blade_status(bladerf_set_lpf_mode(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		BLADERF_LPF_NORMAL));


	int num_samples = time_samples_conversion_.convert_to_samples(time_ms, blade_sampling_rate);

	// BladeRF only accepts data num_samples that are a multiple of 1024.
	num_samples += 1024 - num_samples % 1024;

	const auto return_bytes = num_samples * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	bladerf_metadata metadata;

	check_blade_status(bladerf_rx(comm_blade_rf_->blade_rf(), BLADERF_FORMAT_SC16_Q12,
		aligned_buffer, num_samples, &metadata));


	//aligned_buffer_.get_unaligned_array().output_binary("output_raw.bin");
	//aligned_buffer_.get_unaligned_array().output_text("output_raw.txt");

	measurement_info data(num_samples,
		frequency,
		blade_bandwidth,
		actual_sampling_rate_used,
		time_ms);


	//// 2 * length because we're dealing with complex numbers!
	//ipp_helper::check_status(ippsSwapBytes_16u_I((Ipp16u*)&(*aligned_buffer), num_samples * 2));
	//aligned_buffer_.get_unaligned_array().output_binary("output_raw_swapped.bin");
	//aligned_buffer_.get_unaligned_array().output_text("output_raw_swapped.txt");

	for(int i = 0; i < num_samples * 2; ++i)
		rf_phreaker::sign_extend_12_bits(reinterpret_cast<int16_t*>(aligned_buffer)[i]);

	//aligned_buffer_.get_unaligned_array().output_binary("output_raw_swapped_and_extended.bin");
	//aligned_buffer_.get_unaligned_array().output_text("output_extended.txt");

	ipp_helper::check_status(ippsConvert_16s32f((Ipp16s*)&(*aligned_buffer_.get_aligned_array()), (Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

	////data.get_iq().output_binary("output_formatted.bin");
	data.get_iq().output_text("output_formatted.txt");

	return data;
}

int blade_rf_controller::check_blade_status(int return_status)
{
	if(return_status < 0)
		throw blade_rf_error(bladerf_strerror(return_status), return_status);
	//switch(return_status) {
	//	case BLADERF_ERR_UNEXPECTED:
	//		break;
	//	case BLADERF_ERR_RANGE:
	//		break;
	//	case BLADERF_ERR_INVAL:
	//		break;
	//	case BLADERF_ERR_MEM:
	//		break;
	//	case BLADERF_ERR_IO:
	//		break;
	//	case BLADERF_ERR_TIMEOUT:
	//		break;
	//	case BLADERF_ERR_NODEV:
	//		break;
	//	case BLADERF_ERR_UNSUPPORTED:
	//		break;
	//	case BLADERF_ERR_MISALIGNED:
	//		break;
	//	case BLADERF_ERR_CHECKSUM:
	//		break;
	//	default:
	//	}
	//}
	return return_status;
}
