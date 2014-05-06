#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/scanner/comm_blade_rf.h"
#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/lms_utilities.h"
#include "rf_phreaker/scanner/scanner_utility.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/scanner_blade_rf_impl.h"
#include "libbladeRF.h"
#include "boost/math/special_functions/round.hpp"

namespace rf_phreaker { namespace scanner {

blade_rf_controller::blade_rf_controller(comm_type)
{}

blade_rf_controller::blade_rf_controller(blade_rf_controller &&c)
: comm_blade_rf_(std::move(c.comm_blade_rf_))
, scanner_blade_rf_(std::move(c.scanner_blade_rf_))
{}

blade_rf_controller::~blade_rf_controller()
{
	if(comm_blade_rf_.get())
		bladerf_close(comm_blade_rf_->blade_rf());
}

int blade_rf_controller::num_available_scanners()
{
	std::vector<comm_info_ptr> devices;
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = bladerf_get_device_list(&dev_info);

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV)
		check_blade_status(num_devices);

	return num_devices;
}

std::vector<comm_info_ptr> blade_rf_controller::list_available_scanners()
{
	std::vector<comm_info_ptr> devices;
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = bladerf_get_device_list(&dev_info);

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV)
		check_blade_status(num_devices);

	for(int i = 0; i < num_devices; i++) {
		devices.push_back(comm_info_ptr(new comm_blade_rf(dev_info[i])));
	}

	bladerf_free_device_list(dev_info);

	return devices;
}

void blade_rf_controller::open_scanner(const scanner_id_type &id)
{
	parameter_cache_ = measurement_info();
	gpio_cache_ = 0;

	close_scanner();

	std::string open_str = "libusb:serial=" + id;

	bladerf *blade_rf;

	check_blade_status(bladerf_open(&blade_rf, open_str.c_str()));

	bladerf_devinfo dev_info;

	check_blade_status(bladerf_get_devinfo(blade_rf, &dev_info));

	comm_blade_rf_.reset(new comm_blade_rf(dev_info, blade_rf));

	refresh_scanner_info();

	LOG_L(DEBUG) << "Opened scanner " << scanner_blade_rf_->serial() << ".  Device speed is " << to_string(scanner_blade_rf_->usb_speed()) << ". VCTCXO trim value is " << scanner_blade_rf_->vctcxo_trim() << ".";
}

void blade_rf_controller::refresh_scanner_info()
{
	check_blade_comm();

	scanner_blade_rf_impl blade;

	auto comm_blade = comm_blade_rf_->blade_rf();

	check_blade_status(bladerf_get_devinfo(comm_blade, &blade.dev_info_));

	blade.usb_speed_ = static_cast<bladerf_dev_speed>(check_blade_status(bladerf_device_speed(comm_blade_rf_->blade_rf())));

	// bladerf_stats is not currently supported.  FPGA needs to support behavior.
	//check_blade_status(bladerf_stats(comm_blade, &blade.stats_));
	//blade.stats_.rx_overruns = 0;
	//blade.stats_.rx_throughput = 0;
	//blade.stats_.tx_throughput = 0;
	//blade.stats_.tx_underruns = 0;

	bladerf_version(&blade.blade_rf_version_);

	check_blade_status(bladerf_fw_version(comm_blade, &blade.firmware_version_));

	check_blade_status(bladerf_fpga_version(comm_blade, &blade.fpga_version_));

	blade.rx_timeout_ = 0;

	check_blade_status(bladerf_get_vctcxo_trim(comm_blade, &blade.vctcxo_trim_value_));

	// TODO - Temporary measure until we add trim value date to calibration info.
	time_t date = 0;
	uint16_t value = 0;
	if(scanner_blade_rf_ && scanner_blade_rf_->serial() == blade.serial()) {
		date = scanner_blade_rf_->get_frequency_correction_date();
		value = scanner_blade_rf_->get_frequency_correction_value();
	}
	scanner_blade_rf_ = std::make_shared<scanner_blade_rf>(blade);
	if(date || value) {
		scanner_blade_rf_->set_vctcxo_trim_date(date);
		scanner_blade_rf_->set_vctcxo_trim_value(value);
	}
}


void blade_rf_controller::close_scanner()
{
	if(comm_blade_rf_.get()) {
		bladerf_close(comm_blade_rf_->blade_rf());
		comm_blade_rf_.reset();
	}
}

void blade_rf_controller::do_initial_scanner_config()
{
	check_blade_comm();

	std::string id = comm_blade_rf_->id();

	// When errors opening and configuring occur they seem to be fixed
	// by restarting the entire process hence if an error occurs anywhere 
	// within the open/configure process we restart.
	while(1) {
		int retry = 0;
		try {
			check_blade_status(bladerf_load_fpga(comm_blade_rf_->blade_rf(),
				"fpga_load.rbf"));

			int status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_LPF_TUNING));
				if(status == 0) break;
				LOG_L(DEBUG) << "Calibration attempt failed: LPF Tuning Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: LPF Tuning Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = check_blade_status(bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RX_LPF));
				if(status == 0) break;
				LOG_L(DEBUG) << "Calibration attempt failed: DC RX LPT Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RX LPT Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RXVGA2));
				if(status == 0) break;
				LOG_L(DEBUG) << "Calibration attempt failed: DC RXVGA2 Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RXVGA2 Module.");

			check_blade_status(bladerf_set_lpf_mode(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
				BLADERF_LPF_NORMAL));

			break;
		}
		catch(rf_phreaker_error &err) {
			if(++retry > 3)
				throw err;

			LOG_L(DEBUG) << err.what() << "  Attempting to recover...";

			close_scanner();
			for(int i = 0; i < 3; ++i) {
				std::this_thread::sleep_for(std::chrono::seconds(3));
				open_scanner(id);
				std::this_thread::sleep_for(std::chrono::seconds(1));
				break;
			}
		}
	}

	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_TX,
		false));

	check_blade_status(bladerf_expansion_gpio_dir_write(comm_blade_rf_->blade_rf(), 0xFFFFFFFF));

	enable_blade_rx();

	//bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_DEBUG);

	// construction of licensing
	// construction of calibration table
}

void blade_rf_controller::enable_blade_rx()
{
#ifdef _DEBUG
	check_blade_status(bladerf_sync_config(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		32, 1024 * 16, 16, 1000));
#else
	check_blade_status(bladerf_sync_config(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		12, 1024 * 16, 8, 1000));
#endif

	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		true));
}

void blade_rf_controller::disable_blade_rx()
{
	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		false));
}



void blade_rf_controller::write_vctcxo_trim(frequency_type carrier_freq, frequency_type freq_shift)
{
	auto trim = calculate_vctcxo_trim_value(carrier_freq, freq_shift);
	update_vctcxo_trim(trim);
	write_vctcxo_trim(trim);
}

uint16_t blade_rf_controller::calculate_vctcxo_trim_value(frequency_type carrier_freq, frequency_type freq_shift)
{
	check_blade_comm();

	auto adjust = boost::math::round(freq_shift / (carrier_freq / 38.4e6) * 74.5);

	return scanner_blade_rf_->vctcxo_trim() - (int16_t)adjust;
}

void blade_rf_controller::write_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

//	disable_blade_rx();

	auto image = bladerf_alloc_cal_image(BLADERF_FPGA_40KLE, trim);
	if(image == nullptr)
		throw blade_rf_error("Unable to create calibration image.");

	LOG_L(DEBUG) << "Writing vctcxo trim value of " << trim << " to scanner " << comm_blade_rf_->id() << ".";

	check_blade_status(bladerf_program_flash_unaligned(comm_blade_rf_->blade_rf(), image->address,
		image->data, image->length));

//	enable_blade_rx();
	// We must reopen device for it to become effective.

	LOG_L(DEBUG) << "Reopening scanner to initialize with new vctcxo.";
	
	try { get_rf_data(10000); }
	catch(...) {}

	open_scanner(comm_blade_rf_->id());
	do_initial_scanner_config();
}

void blade_rf_controller::update_vctcxo_trim(frequency_type carrier_freq, frequency_type freq_shift)
{
	auto trim = calculate_vctcxo_trim_value(carrier_freq, freq_shift);
	update_vctcxo_trim(trim);
}

void blade_rf_controller::update_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

//	disable_blade_rx();

	check_blade_status(bladerf_dac_write(comm_blade_rf_->blade_rf(), trim));

//	enable_blade_rx();

	scanner_blade_rf_->set_vctcxo_trim_value(trim);

	scanner_blade_rf_->set_vctcxo_trim_date(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
}

void blade_rf_controller::read_vctcxo_trim(uint16_t &trim)
{
	check_blade_comm();

	check_blade_status(bladerf_get_vctcxo_trim(comm_blade_rf_->blade_rf(), &trim));
}

void blade_rf_controller::write_gpio(uint32_t value)
{
	check_blade_comm();

	check_blade_status(bladerf_expansion_gpio_write(comm_blade_rf_->blade_rf(), value));
}

void blade_rf_controller::read_gpio(uint32_t &value)
{
	check_blade_comm();

	check_blade_status(bladerf_expansion_gpio_read(comm_blade_rf_->blade_rf(), &value));
}

void blade_rf_controller::set_lms_reg(uint8_t address, uint8_t value)
{
	check_blade_comm();

	check_blade_status(bladerf_lms_write(comm_blade_rf_->blade_rf(), address, value));
}

void blade_rf_controller::read_lms_reg(uint8_t address, uint8_t &value)
{
	check_blade_comm();

	check_blade_status(bladerf_lms_read(comm_blade_rf_->blade_rf(), address, &value));
}


const rf_phreaker::scanner::scanner* blade_rf_controller::get_scanner()
{
	refresh_scanner_info();

	return scanner_blade_rf_.get();
}

const scanner_blade_rf* blade_rf_controller::get_scanner_blade_rf()
{
	refresh_scanner_info();

	return scanner_blade_rf_.get();
}

gps blade_rf_controller::get_gps_data()
{
	check_blade_comm();
	
	gps g;
	g.scanner_id_ = scanner_blade_rf_->serial();
	g.lock_ = false;
	g.coordinated_universal_time_ = 0;
	g.visible_satellites_ = 0;
	g.tracking_satellites_ = 0;
	g.latitude_ = 0;
	g.longitude_ = 0;
	g.speed_ = 0;
	g.raw_status_ = 0;

	// Simiulate communicating to the hardware.
	uint32_t val = 0;
	//check_blade_status(bladerf_config_gpio_read(comm_blade_rf_->blade_rf(), &val));

	return g;
}

measurement_info blade_rf_controller::get_rf_data_use_auto_gain(frequency_type frequency, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate)
{
	auto gain = get_auto_gain(frequency, bandwidth);

	return get_rf_data(frequency, time_ns, bandwidth, gain, sampling_rate);
}

gain_type blade_rf_controller::get_auto_gain(frequency_type freq, bandwidth_type bandwidth, time_type time_ns,
										frequency_type sampling_rate)
{
	if(gain_manager_.in_history(freq, bandwidth))
		return gain_manager_.calculate_new_gain(freq, bandwidth);

	if(time_ns == 0)
		time_ns = 5000000;

	// Use lowest sampling rate because we only care about the Max ADC.
	sampling_rate = mhz(32);

	// If we have no history loop thru a couple times to zero in on the gain.
	get_rf_data(freq, time_ns, bandwidth, gain_manager_.default_gain(), sampling_rate);
	for(int i = 0; i < 2; ++i) {	
		get_rf_data(freq, time_ns, bandwidth, gain_manager_.calculate_new_gain(freq, bandwidth), sampling_rate);
	}
	return gain_manager_.calculate_new_gain(freq, bandwidth);
}

measurement_info blade_rf_controller::get_rf_data(frequency_type frequency, time_type time_ns, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate)
{
	LOG_L(VERBOSE) << "Taking snapshot... " << "frequency: " << frequency / 1e6 << "mhz | time: "
		<< time_ns / 1e6 << "ms | bandwidth: " << bandwidth / 1e6 
		<< "mhz | sampling_rate: " << sampling_rate / 1e6 << "mhz | gain: "
		<< gain.lna_gain_ << " " << gain.rxvga1_ << " " << gain.rxvga2_;

	check_blade_comm();

	if(parameter_cache_.frequency() != frequency) {
		int status = 0;
		for(int i = 0; i < 10; ++i) {
			status = (bladerf_set_frequency(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
				static_cast<uint32_t>(frequency)));
			if(status == 0) break;
			LOG_L(DEBUG) << "Setting frequency (" << frequency / 1e6 << "mhz) failed. Retrying...";
		}
		if(status)
			throw blade_rf_error(std::string("Error setting frequency.  ") + bladerf_strerror(status));
	}

	// Per Nyquist a signal must be sampled at a rate greater than twice it's maximum frequency component.  Thus
	// once converted to baseband the highest pertinent frequency component will be 1/2 the bandwidth so our sampling 
	// rate should be a little greater than our bandwidth.
	if(sampling_rate == 0)
		sampling_rate = static_cast<frequency_type>(bandwidth * 1.2);

	if(parameter_cache_.gain().lna_gain_ != gain.lna_gain_) {
		check_blade_status(bladerf_set_lna_gain(comm_blade_rf_->blade_rf(), convert(gain.lna_gain_)));
	}
	if(parameter_cache_.gain().rxvga1_ != gain.rxvga1_) {
		check_blade_status(bladerf_set_rxvga1(comm_blade_rf_->blade_rf(), gain.rxvga1_));
	}
	if(parameter_cache_.gain().rxvga2_ != gain.rxvga2_) {
		check_blade_status(bladerf_set_rxvga2(comm_blade_rf_->blade_rf(), gain.rxvga2_));
	}
	
	unsigned int blade_sampling_rate = 0;
	unsigned int blade_bandwidth = 0;

	if(parameter_cache_.sampling_rate() != sampling_rate) {
		check_blade_status(bladerf_set_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			static_cast<uint32_t>(sampling_rate), &blade_sampling_rate));
	}
	else
		blade_sampling_rate = static_cast<uint32_t>(parameter_cache_.sampling_rate());

	if(parameter_cache_.bandwidth() != bandwidth) {
		check_blade_status(bladerf_set_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			bandwidth, &blade_bandwidth));
	}
	else
		blade_bandwidth = parameter_cache_.bandwidth();

	uint32_t gpio = rf_switch_conversion_.convert_to_gpio(frequency, bandwidth, 0);
	if(gpio_cache_ != gpio) {
		check_blade_status(bladerf_expansion_gpio_write(comm_blade_rf_->blade_rf(),
			rf_switch_conversion_.convert_to_gpio(frequency, bandwidth, gpio)));
		gpio_cache_ = gpio;
	}

	// BladeRF only accepts data num_samples that are a multiple of 1024.
	int throw_away_samples = 10240*2;
	throw_away_samples += 1024 - throw_away_samples % 1024;

	int num_samples = rf_phreaker::convert_to_samples(time_ns, blade_sampling_rate);
	auto num_samples_to_transfer = num_samples + 1024 - num_samples % 1024;

	const auto return_bytes = (num_samples_to_transfer + throw_away_samples) * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	bladerf_metadata metadata;

	int status = 0;
	for(int i = 0; i < 10; ++i) {
#ifdef _DEBUG
		while(bladerf_wait_for_rx_idle(comm_blade_rf_->blade_rf())) {};

		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples_to_transfer + throw_away_samples, &metadata, 0);
#else
		check_blade_status(bladerf_wait_for_rx_idle(comm_blade_rf_->blade_rf()));
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples_to_transfer + throw_away_samples, &metadata, 1000);
#endif
		if(status == 0) break;
		LOG_L(DEBUG) << "Collecting " << num_samples_to_transfer + throw_away_samples << " samples failed. Status = " << status << ". Retrying...";
		disable_blade_rx();
		enable_blade_rx();
	}
	if(status)
		throw blade_rf_error(std::string("Error collecting data samples.  ") + bladerf_strerror(status));
	
	parameter_cache_ = measurement_info(0, frequency, blade_bandwidth, blade_sampling_rate , gain);

	measurement_info data(num_samples, frequency, blade_bandwidth, blade_sampling_rate, gain);

	for(int i = throw_away_samples; i < (throw_away_samples + num_samples) * 2; ++i)
		sign_extend_12_bits(reinterpret_cast<int16_t*>(aligned_buffer)[i]);

	const auto beginning_of_iq = (Ipp16s*)&(*aligned_buffer_.get_aligned_array()) + (throw_away_samples * 2);

	ipp_helper::check_status(ippsConvert_16s32f(beginning_of_iq,
		(Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

	gain_manager_.update_gain(data);

	ipp_helper::subtract_dc(data.get_iq().get(), data.get_iq().length());

	return data;
}

measurement_info blade_rf_controller::get_rf_data(int num_samples)
{
	uint32_t frequency;
	uint32_t blade_bandwidth;
	uint32_t blade_sampling_rate;
	bladerf_lna_gain tmp_lna_gain;
	gain_type gain;

	check_blade_status(bladerf_get_lna_gain(comm_blade_rf_->blade_rf(), &tmp_lna_gain));
	gain.lna_gain_ = convert(tmp_lna_gain);

	check_blade_status(bladerf_get_rxvga1(comm_blade_rf_->blade_rf(), &gain.rxvga1_));

	check_blade_status(bladerf_get_rxvga2(comm_blade_rf_->blade_rf(), &gain.rxvga2_));

	check_blade_status(bladerf_get_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		&blade_sampling_rate));

	check_blade_status(bladerf_get_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		&blade_bandwidth));

	check_blade_status(bladerf_get_frequency(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			&frequency));

	// BladeRF only accepts data num_samples that are a multiple of 1024.
	num_samples += 1024 - num_samples % 1024;

	const auto return_bytes = num_samples * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	bladerf_metadata metadata;

	check_blade_status(bladerf_wait_for_rx_idle(comm_blade_rf_->blade_rf()));

	int status = 0;
	for(int i = 0; i < 10; ++i) {
#ifdef _DEBUG
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			return_bytes, &metadata, 0);
#else
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			return_bytes, &metadata, 1000);
#endif
		if(status == 0) break;
		LOG_L(DEBUG) << "Collecting " << return_bytes << " samples failed. Retrying...";
	}
	if(status)
		throw blade_rf_error(std::string("Error collecting data samples.  ") + bladerf_strerror(status));

	measurement_info data(num_samples, frequency, blade_bandwidth, blade_sampling_rate,
						  gain);

	for(int i = 0; i < num_samples * 2; ++i)
		sign_extend_12_bits(reinterpret_cast<int16_t*>(aligned_buffer)[i]);

	ipp_helper::check_status(ippsConvert_16s32f((Ipp16s*)&(*aligned_buffer_.get_aligned_array()),
		(Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

	ipp_helper::subtract_dc(data.get_iq().get(), data.get_iq().length());

	return data;
}

int blade_rf_controller::check_blade_status(int return_status)
{
	if(return_status < 0)
		throw blade_rf_error(bladerf_strerror(return_status), return_status);
	return return_status;
}

void blade_rf_controller::check_blade_comm()
{
	if(comm_blade_rf_.get() == nullptr)
		throw rf_phreaker::comm_error("It does not appear there is a valid connection to the device.  Try opening the device.");
}

}}