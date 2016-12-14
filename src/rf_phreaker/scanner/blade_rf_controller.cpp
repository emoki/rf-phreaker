#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/scanner/comm_blade_rf.h"
#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/lms_utilities.h"
#include "rf_phreaker/scanner/scanner_utility.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/scanner_blade_rf_impl.h"
#include "rf_phreaker/scanner/nr_interface.h"
#include "libbladeRF.h"
#include "boost/math/special_functions/round.hpp"
#include "boost/date_time.hpp"

namespace rf_phreaker { namespace scanner {

blade_rf_controller::blade_rf_controller(comm_type)
	: collection_count_(0)
	, streaming_time_ns_(-1)
	, streaming_time_ns_to_overlap_(-1) {
	is_streaming_ = NOT_STREAMING;
	meas_buffer_.set_capacity(20);
	nr_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
}

blade_rf_controller::blade_rf_controller(blade_rf_controller &&c)
	: comm_blade_rf_(std::move(c.comm_blade_rf_))
	, scanner_blade_rf_(std::move(c.scanner_blade_rf_))
	, collection_count_(std::move(c.collection_count_))
	, meas_buffer_(std::move(c.meas_buffer_))
	, blade_settings_(std::move(blade_settings_))
	, blade_settings_stream_(std::move(blade_settings_stream_)) 
	, streaming_time_ns_(-1)
	, streaming_time_ns_to_overlap_(-1) {
	is_streaming_ = NOT_STREAMING;
}

blade_rf_controller::~blade_rf_controller()
{
	close_scanner();
}

int blade_rf_controller::num_available_scanners()
{
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = nr_get_device_list(&dev_info);

	// Sometimes the API reports 0 devices connected even tho we have a scanner connected. 
	// In which case we repeat the call.
	if(num_devices == BLADERF_ERR_NODEV) {
		for(int i = 0; i < 4; ++i) {
			num_devices = nr_get_device_list(&dev_info);
			if(num_devices > 0)
				break;
		}
	}

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV && num_devices < 0) {
		nr_free_device_list(dev_info);
		check_blade_status(num_devices, __FILE__, __LINE__);
	}

	nr_free_device_list(dev_info);

	return num_devices == BLADERF_ERR_NODEV ? 0 : num_devices;
}

std::vector<comm_info_ptr> blade_rf_controller::list_available_scanners()
{
	std::vector<comm_info_ptr> devices;
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = nr_get_device_list(&dev_info);

	// Sometimes the API reports 0 devices connected even tho we have a scanner connected. 
	// In which case we repeat the call.
	if(num_devices == BLADERF_ERR_NODEV) {
		for(int i = 0; i < 2; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			num_devices = nr_get_device_list(&dev_info);
			if(num_devices > 0)
				break;
		}
	}

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV && num_devices < 0) {
		if(dev_info)
			nr_free_device_list(dev_info);
		check_blade_status(num_devices, __FILE__, __LINE__);
	}

	for(int i = 0; i < num_devices; i++) {
		devices.push_back(comm_info_ptr(new comm_blade_rf(dev_info[i])));
	}

	nr_free_device_list(dev_info);

	return devices;
}

void blade_rf_controller::open_scanner_and_refresh_scanner_info(const scanner_serial_type &id) {
	open_scanner(id);
	refresh_scanner_info();
}

void blade_rf_controller::open_scanner(const scanner_serial_type &id)
{
	set_parameter_cache(measurement_info());

	std::lock_guard<std::recursive_mutex> lock(open_close_mutex_);
	if(comm_blade_rf_.get()) {
		close_scanner();
		// If we close the scanner, we have to list devices.  It somehow release a mutex that
		// is still being held.  Recheck this behavior after we upgrade bladerf.
		list_available_scanners();
	}

	std::string open_str = "*:serial=" + id;

	bladerf *blade_rf;
	bladerf_devinfo dev_info;
	int retry = 0;
	while(1) {
		try {
			// If the FPGA is in a bad state we want to make sure we don't access it while opening even if
			// the bladeRF says the FPGA is loaded.  Setting this environmental variable allows us to do that.
			LOG_IF(LERROR, (rf_phreaker::setenv("BLADERF_FORCE_NO_FPGA_PRESENT", "1", 1) != 0)) 
				<< "Unable to set force_no_fpga_present variable.";

			check_blade_status(nr_open(&blade_rf, open_str.c_str(), __FILE__, __LINE__), __FILE__, __LINE__);

			check_blade_status(nr_get_devinfo(blade_rf, &dev_info, __FILE__, __LINE__), __FILE__, __LINE__);

			// Remove this value so we can update the vctcxo trim value, which requires implicit use of the FPGA.
			LOG_IF(LERROR, (rf_phreaker::setenv("BLADERF_FORCE_NO_FPGA_PRESENT", "", 1) != 0)) 
				<< "Unable to remove force_no_fpga_present variable.";
			break;
		}
		catch(rf_phreaker_error &err) {
			if(++retry > 2)
				throw err;
			LOG(LDEBUG) << err.what() << "  Attempting to reopen...";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	comm_blade_rf_.reset(new comm_blade_rf(dev_info, blade_rf));
}

measurement_info blade_rf_controller::parameter_cache() {
	std::lock_guard<std::mutex> lock(parameter_cache_mutex_);
	return parameter_cache_;
}

void blade_rf_controller::set_parameter_cache(measurement_info &info) {
	std::lock_guard<std::mutex> lock(parameter_cache_mutex_);
	parameter_cache_ = info;
}

void blade_rf_controller::refresh_scanner_info()
{
	check_blade_comm();

	scanner_blade_rf_impl blade;

	auto comm_blade = comm_blade_rf_->blade_rf();

	check_blade_status(nr_get_devinfo(comm_blade, &blade.dev_info_, __FILE__, __LINE__), __FILE__, __LINE__);

	blade.usb_speed_ = nr_device_speed(comm_blade_rf_->blade_rf());

	nr_version(&blade.blade_rf_version_);

	check_blade_status(nr_fw_version(comm_blade, &blade.firmware_version_), __FILE__, __LINE__);

	check_blade_status(nr_fpga_version(comm_blade, &blade.fpga_version_), __FILE__, __LINE__);

	blade.rx_timeout_ = 0;

	check_blade_status(nr_get_vctcxo_trim(comm_blade, &blade.vctcxo_trim_value_, __FILE__, __LINE__), __FILE__, __LINE__);

	try {
		blade.eeprom_ = read_eeprom();
	}
	catch(rf_phreaker_error &err) {
		LOG(LERROR) << "Error reading EEPROM.  " << err.what();
		delegate_sink::instance().log_error(std::string("Error reading EEPROM.  ") + err.what(), err.error_type_, EEPROM_ERROR);
	}
	catch(std::exception &err) {
		LOG(LERROR) << "Error reading EEPROM.  " << err.what();
		delegate_sink::instance().log_error(std::string("Error reading EEPROM.  ") + err.what(), generic_error_type, EEPROM_ERROR);
	}

	if(!scanner_blade_rf_) {
		scanner_blade_rf_ = std::make_shared<scanner_blade_rf_impl>(blade);
		scanner_ = std::make_shared<scanner_blade_rf>(scanner_blade_rf_.get());
	}
	else {
		*scanner_blade_rf_ = blade;
		*scanner_ = scanner_blade_rf_.get();
	}

	update_vctcxo_based_on_eeprom();

	LOG(LDEBUG) << "Scanner serial is " << scanner_blade_rf_->serial() << ".";
	LOG(LDEBUG) << "Scanner ID is " << scanner_blade_rf_->eeprom_.cal_.hw_id_ << ".";
	LOG(LDEBUG) << "USB backend is " << usb_backend_to_string(scanner_blade_rf_->back_end()) << ".";
	LOG(LDEBUG) << "Device speed is " << to_string(scanner_blade_rf_->usb_speed()) << ".";
	LOG(LDEBUG) << "Blade library version is " << scanner_blade_rf_->blade_rf_version_description() << ".";
	LOG(LDEBUG) << "Blade firmware version is " << scanner_blade_rf_->firmware_version_description() << ".";
	LOG(LDEBUG) << "RF calibration performed on " << boost::posix_time::to_simple_string(boost::posix_time::from_time_t(scanner_blade_rf_->get_rf_calibration_date())) << ".";
	LOG(LDEBUG) << "VCTCXO trim value is " << scanner_blade_rf_->vctcxo_trim() << ".";
	LOG(LDEBUG) << "Frequency correction performed on " << boost::posix_time::to_simple_string(boost::posix_time::from_time_t(scanner_blade_rf_->get_frequency_correction_date())) << ".";
	LOG(LDEBUG) << "Frequency correction value is " << scanner_blade_rf_->get_frequency_correction_value() << ".";
}

void blade_rf_controller::update_vctcxo_based_on_eeprom() {
	if(scanner_blade_rf_ && std::string(scanner_blade_rf_->fpga_version_.describe).size() && scanner_blade_rf_->eeprom_.freq_correction_.nuand_freq_correction_value_) {
		update_vctcxo_trim(scanner_blade_rf_->eeprom_.freq_correction_.nuand_freq_correction_value_);
	}
}

void blade_rf_controller::close_scanner()
{
	// Only stop our streaming thread - disabling the RX stream will occur inside the bladeRF API close function.
	stop_streaming();
	std::lock_guard<std::recursive_mutex> lock(open_close_mutex_);
	if(comm_blade_rf_.get()) {
		nr_close(comm_blade_rf_->blade_rf());
		comm_blade_rf_.reset();
		scanner_blade_rf_.reset();
		scanner_.reset();
		gps_comm_.reset();
	}
	static_timestamp::clear();
}

void blade_rf_controller::do_initial_scanner_config(const scanner_settings &settings)
{
	check_blade_comm();

	std::string id = comm_blade_rf_->id();

	update_settings(settings);

	// When errors opening and configuring occur they seem to be fixed
	// by restarting the entire process hence if an error occurs anywhere 
	// within the open/configure process we restart.
	int retry = 0;
	while(1) {
		try {
			check_blade_status(nr_load_fpga(comm_blade_rf_->blade_rf(),
				"fpga_load.rbf", __FILE__, __LINE__), __FILE__, __LINE__);

			int status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (nr_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_LPF_TUNING, __FILE__, __LINE__));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: LPF Tuning Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: LPF Tuning Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = check_blade_status(nr_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RX_LPF, __FILE__, __LINE__));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: DC RX LPT Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RX LPT Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (nr_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RXVGA2, __FILE__, __LINE__));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: DC RXVGA2 Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RXVGA2 Module.");

			check_blade_status(nr_set_lpf_mode(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
				BLADERF_LPF_NORMAL, __FILE__, __LINE__), __FILE__, __LINE__);

			break;
		}
		catch(rf_phreaker_error &err) {
			if(++retry > 1)
				throw err;

			LOG(LDEBUG) << err.what() << "  Attempting to recover...";

			close_scanner();
			for(int i = 0; i < 1; ++i) {
				std::this_thread::sleep_for(std::chrono::seconds(2));
				open_scanner_and_refresh_scanner_info(id);
				std::this_thread::sleep_for(std::chrono::seconds(1));
				break;
			}
		}
	}

	// Update scanner fpga version because we loaded the FPGA.
	if(scanner_blade_rf_) {
		check_blade_status(nr_fpga_version(comm_blade_rf_->blade_rf(), &scanner_blade_rf_->fpga_version_, __FILE__, __LINE__), __FILE__, __LINE__);
		LOG(LDEBUG) << "Blade fpga version is " << scanner_blade_rf_->fpga_version_description() << ".";
	}

	check_blade_status(nr_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_TX,
		false), __FILE__, __LINE__);

	// TODO - Change this so that we only alter switch settings.
	check_blade_status(nr_expansion_gpio_dir_write(comm_blade_rf_->blade_rf(), 0xFFFFFFFF, __FILE__, __LINE__), __FILE__, __LINE__);

	update_vctcxo_based_on_eeprom();

	power_on_gps();
}

void blade_rf_controller::update_settings(const scanner_settings &settings) {
	stop_streaming_and_disable_blade_rx();
	auto &blade = reinterpret_cast<const blade_settings&>(settings);
	set_blade_sync_rx_settings(blade.intermittent_streaming_rx_);
	set_blade_sync_rx_stream_settings(blade.full_streaming_rx_);
	set_log_level(blade.log_level_);
}

void blade_rf_controller::enable_blade_rx(const blade_rx_settings &settings)
{
	check_blade_comm();
	auto tmp = settings;
	if(tmp.rx_sync_buffer_size_ % 1024 != 0) {
		tmp.rx_sync_buffer_size_ = add_mod(tmp.rx_sync_buffer_size_, 1024);
		LOG(LWARNING) << "The nr rx sync buffer size is not a multiple of 1024.  Adjusting value to " << tmp.rx_sync_buffer_size_ << ".";
	}

	check_blade_status(nr_sync_config(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		tmp.rx_sync_num_buffers_, tmp.rx_sync_buffer_size_, tmp.rx_sync_num_transfers_,
		tmp.rx_sync_timeout_, __FILE__, __LINE__), __FILE__, __LINE__);

	check_blade_status(nr_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		true, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::enable_full_streaming_rx() {
	enable_blade_rx(blade_settings_stream_);
	is_streaming_ = FULL_STREAMING;
}

void blade_rf_controller::enable_intermittent_streaming_rx() {
	enable_blade_rx(blade_settings_);
	is_streaming_ = INTERMITTENT_STREAMING;
}

void blade_rf_controller::stop_streaming_and_disable_blade_rx() {
	stop_streaming();
	if(comm_blade_rf_.get()) {
		disable_blade_rx();
	}
}

void blade_rf_controller::disable_blade_rx()
{
	check_blade_comm();
	check_blade_status(nr_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		false, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::power_on_gps() {
	check_blade_comm();
	gps_comm_.reset(new gps_comm::gps_comm());
	gps_comm_->init(comm_blade_rf_->blade_rf(), false);
}

void blade_rf_controller::power_off_gps() {
	if(gps_comm_) {
		gps_comm_->power_off();
		gps_comm_.reset();
	}
}

void blade_rf_controller::calculate_vctcxo_trim_and_update_eeprom(double error_hz)
{
	auto trim = calculate_vctcxo_trim_value(error_hz);
	update_vctcxo_trim(trim);
	write_vctcxo_trim(trim);
	update_frequency_correction_value_and_date_in_calibration(trim, std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
	refresh_scanner_info();
}

uint16_t blade_rf_controller::calculate_vctcxo_trim_value(double error_hz)
{
	check_blade_comm();

	auto adjust = boost::math::round(error_hz / dac_trim_hz_per_lsb_coefficient()/* * .9*/);

	return scanner_blade_rf_->vctcxo_trim() - (int16_t)adjust;
}

void blade_rf_controller::write_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

	stop_streaming_and_disable_blade_rx();

	auto image = nr_alloc_cal_image(BLADERF_FPGA_40KLE, trim, __FILE__, __LINE__);
	if(image == nullptr)
		throw blade_rf_error("Unable to create BLADERF_FPGA_40KLE image.");

	LOG(LDEBUG) << "Writing vctcxo trim value of " << trim << " to scanner " << comm_blade_rf_->id() << ".";

	auto page = BLADERF_FLASH_TO_PAGES(image->address);
	auto count = BLADERF_FLASH_TO_PAGES(image->length);

	check_blade_status(nr_erase_flash(comm_blade_rf_->blade_rf(), BLADERF_FLASH_EB_CAL, BLADERF_FLASH_EB_LEN_CAL, __FILE__, __LINE__), __FILE__, __LINE__);
	check_blade_status(nr_write_flash(comm_blade_rf_->blade_rf(), image->data, page, count, __FILE__, __LINE__), __FILE__, __LINE__);

	nr_free_image(image);
}

void blade_rf_controller::update_frequency_correction_value_and_date_in_calibration(uint16_t value, time_t date)
{
	freq_correction_container corr;
	corr.nuand_freq_correction_value_ = value;
	corr.nuand_freq_correction_date_ = date;
	write_frequency_correction(corr);
}

void blade_rf_controller::calculate_and_update_vctcxo_trim(double error_hz)
{
	auto trim = calculate_vctcxo_trim_value(error_hz);
	update_vctcxo_trim(trim);
}

void blade_rf_controller::update_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

	LOG(LDEBUG) << "Updating VCTCXO trim value to " << trim << ".";

	check_blade_status(nr_dac_write(comm_blade_rf_->blade_rf(), trim, __FILE__, __LINE__), __FILE__, __LINE__);
	
	if(scanner_blade_rf_)
		scanner_blade_rf_->vctcxo_trim_value_ = trim;
}

void blade_rf_controller::read_vctcxo_trim(uint16_t &trim)
{
	check_blade_comm();

	if(scanner_blade_rf_)
		trim = scanner_blade_rf_->vctcxo_trim_value_;
	else
		check_blade_status(nr_get_vctcxo_trim(comm_blade_rf_->blade_rf(), &trim, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::write_gpio(uint32_t value) {
	check_blade_comm();

	check_blade_status(nr_expansion_gpio_write(comm_blade_rf_->blade_rf(), value, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::read_gpio(uint32_t &value) {
	check_blade_comm();

	check_blade_status(nr_expansion_gpio_read(comm_blade_rf_->blade_rf(), &value, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::write_config_gpio(uint32_t value) {
	check_blade_comm();

	check_blade_status(nr_config_gpio_write(comm_blade_rf_->blade_rf(), value, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::read_config_gpio(uint32_t &value) {
	check_blade_comm();

	check_blade_status(nr_config_gpio_read(comm_blade_rf_->blade_rf(), &value, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::set_lms_reg(uint8_t address, uint8_t value)
{
	check_blade_comm();

	check_blade_status(nr_lms_write(comm_blade_rf_->blade_rf(), address, value, __FILE__, __LINE__), __FILE__, __LINE__);
}

void blade_rf_controller::read_lms_reg(uint8_t address, uint8_t &value)
{
	check_blade_comm();

	check_blade_status(nr_lms_read(comm_blade_rf_->blade_rf(), address, &value, __FILE__, __LINE__), __FILE__, __LINE__);
}

const rf_phreaker::scanner::scanner* blade_rf_controller::get_scanner()
{
	return get_scanner_blade_rf();
}

const scanner_blade_rf* blade_rf_controller::get_scanner_blade_rf()
{
	return scanner_.get();
}

gps blade_rf_controller::get_gps_data()
{
	check_blade_comm();
	if(gps_comm_)
		return gps_comm_->get_latest_gps();
	else 
		return gps{"", false, 0, 0, 0, 0, 0, 0, 0};
}

measurement_info blade_rf_controller::get_rf_data_use_auto_gain(frequency_type frequency, time_type time_ns, bandwidth_type bandwidth, frequency_type sampling_rate)
{
	auto gain = get_auto_gain(frequency, bandwidth, 5000000, sampling_rate);

	return get_rf_data(frequency, time_ns, bandwidth, gain, sampling_rate);
}

gain_type blade_rf_controller::get_auto_gain(frequency_type freq, bandwidth_type bandwidth, time_type time_ns,
										frequency_type sampling_rate)
{
	if(gain_manager_.is_gain_valid(freq, bandwidth))
		return gain_manager_.calculate_new_gain(freq, bandwidth);

	if(time_ns == 0)
		time_ns = 5000000;

	// If we have no history loop thru a couple times to zero in on the gain.
	get_rf_data(freq, time_ns, bandwidth, gain_manager_.default_gain(), sampling_rate);
	for(int i = 0; i < 2; ++i) {	
		get_rf_data(freq, time_ns, bandwidth, gain_manager_.calculate_new_gain(freq, bandwidth), sampling_rate);
	}
	return gain_manager_.calculate_new_gain(freq, bandwidth);
}

measurement_info blade_rf_controller::get_rf_data(frequency_type frequency, time_type time_ns, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate,
	uint32_t switch_setting, uint32_t switch_mask) {
	configure_rf_parameters(frequency, bandwidth, gain, sampling_rate, switch_setting, switch_mask);

	auto cache = parameter_cache();
	auto blade_bandwidth = (uint32_t)cache.bandwidth();
	auto blade_sampling_rate = (uint32_t)cache.sampling_rate();

	// BladeRF only accepts data num_samples that are a multiple of 1024.
	// Because the blade rx sync parameters are configurable we want to make sure we 
	// clear out every buffer.
	int throw_away_samples = blade_settings_.rx_sync_buffer_size_ * blade_settings_.rx_sync_num_buffers_;

	int num_samples = rf_phreaker::convert_to_samples(time_ns, blade_sampling_rate);
	auto num_samples_to_transfer = add_mod(num_samples, 1024);

	const auto return_bytes = (num_samples_to_transfer + throw_away_samples) * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	if(is_streaming_ != INTERMITTENT_STREAMING) {
		stop_streaming();
		enable_intermittent_streaming_rx();
	}

	bladerf_metadata metadata;
	metadata.flags = BLADERF_META_FLAG_RX_NOW;

	int status = 0;
	for(int i = 0; i < 2; ++i) {
		status = nr_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples_to_transfer + throw_away_samples, &metadata, 2500);
		if(status == 0)
			break;
		else if(is_streaming_ != INTERMITTENT_STREAMING) {
			throw blade_rf_error("Intermittent streaming was cancelled.");
		}
		else {
			LOG(LDEBUG) << "Collecting " << num_samples_to_transfer + throw_away_samples << " samples failed. Status = " << status << ". Retrying...";
			enable_intermittent_streaming_rx();
		}
	}
	if(status)
		throw blade_rf_error(std::string("Error collecting data samples.  ") + nr_strerror(status));

	// For now we use the computer time.  In the future perhaps we can use timestamp coming from the hardware.
	auto start_time = get_collection_start_time();

	measurement_info data(num_samples, frequency, blade_bandwidth, blade_sampling_rate, gain,
		std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time),
		scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustments(gain.lna_gain_, frequency, blade_bandwidth),
		scanner_blade_rf_->eeprom_.cal_.get_rf_board_adjustments(frequency, blade_bandwidth, blade_bandwidth),
		collection_count_++, scanner_blade_rf_->eeprom_.cal_.nuand_serial_);

	const auto beginning_of_iq = (Ipp16s*)&(*aligned_buffer_.get_aligned_array()) + (throw_away_samples * 2);

	ipp_helper::check_status(ippsConvert_16s32f(beginning_of_iq,
		(Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

	update_gain(data);

	ipp_helper::subtract_dc(data.get_iq().get(), data.get_iq().length());

	return data;
}

void blade_rf_controller::update_gain(const measurement_info &info) {
	auto lna_bypass = scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustment(lms::LNA_BYPASS, info.frequency());
	auto lna_mid = scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustment(lms::LNA_MID, info.frequency());
	auto lna_max = scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustment(lms::LNA_MAX, info.frequency());
	gain_manager_.update_gain(info, lna_bypass, lna_mid, lna_max);
}

std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration> blade_rf_controller::get_collection_start_time() {
	static auto start_time = std::chrono::high_resolution_clock::now();
	return start_time;
}

void blade_rf_controller::configure_rf_parameters_use_auto_gain(frequency_type frequency, bandwidth_type bandwidth, frequency_type sampling_rate) {
	auto gain = get_auto_gain(frequency, bandwidth, 5000000, sampling_rate);
	configure_rf_parameters(frequency, bandwidth, gain, sampling_rate);
}

void blade_rf_controller::configure_rf_parameters(frequency_type frequency, bandwidth_type bandwidth, const gain_type &gain, frequency_type sampling_rate,
	uint32_t switch_setting, uint32_t switch_mask) {
	LOG(LCOLLECTION) << "Configuring scanner... " << "frequency: " << frequency / 1e6 << "mhz | bandwidth: " 
		<< bandwidth / 1e6 << "mhz | sampling_rate: " << sampling_rate / 1e6 << "mhz | gain: "
		<< gain.lna_gain_ << " " << gain.rxvga1_ << " " << gain.rxvga2_;

	check_blade_comm();

	auto cache = parameter_cache();

	if(cache.frequency() != frequency) {
		int status = 0;
		for(int i = 0; i < 2; ++i) {
			status = (nr_set_frequency(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
				static_cast<uint32_t>(frequency), __FILE__, __LINE__));
			if(status == 0) break;
			LOG(LDEBUG) << "Setting frequency (" << frequency / 1e6 << "mhz) failed. Retrying...";
		}
		if(status)
			throw blade_rf_error(std::string("Error setting frequency.  ") + nr_strerror(status));
	}

	// Per Nyquist a signal must be sampled at a rate greater than twice it's maximum frequency component.  Thus
	// once converted to baseband the highest pertinent frequency component will be 1/2 the bandwidth so our sampling 
	// rate should be a little greater than our bandwidth.
	if(sampling_rate == 0)
		sampling_rate = static_cast<frequency_type>(bandwidth * 1.2);

	set_gain(gain);

	unsigned int blade_sampling_rate = 0;
	unsigned int blade_bandwidth = 0;

	if(cache.sampling_rate() != sampling_rate) {
		check_blade_status(nr_set_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			static_cast<uint32_t>(sampling_rate), &blade_sampling_rate, __FILE__, __LINE__), __FILE__, __LINE__);
	}
	else
		blade_sampling_rate = static_cast<uint32_t>(cache.sampling_rate());

	if(cache.bandwidth() != bandwidth) {
		check_blade_status(nr_set_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			bandwidth, &blade_bandwidth, __FILE__, __LINE__), __FILE__, __LINE__);
	}
	else
		blade_bandwidth = cache.bandwidth();

	uint32_t gpio_in_hw = 0;
	check_blade_status(nr_expansion_gpio_read(comm_blade_rf_->blade_rf(),
		&gpio_in_hw, __FILE__, __LINE__), __FILE__, __LINE__);
	LOG(LCOLLECTION) << "Current xb gpio: " << gpio_in_hw << ".";

	if(switch_mask == 0) {
		auto auto_switch_setting = scanner_blade_rf_->eeprom_.cal_.get_rf_switch(frequency, blade_bandwidth);
		switch_setting = auto_switch_setting.switch_setting_;
		switch_mask = auto_switch_setting.switch_mask_;
	}
	if((gpio_in_hw & switch_mask) != switch_setting) {
		uint32_t check = 0;
		for(int i = 0; i < 3; ++i) {
			gpio_in_hw &= ~switch_mask;
			uint32_t new_gpio = gpio_in_hw | switch_setting;
			check_blade_status(nr_expansion_gpio_write(comm_blade_rf_->blade_rf(),
				new_gpio, __FILE__, __LINE__), __FILE__, __LINE__);
			LOG(LCOLLECTION) << "Setting xb gpio to " << new_gpio << ".";
			check_blade_status(nr_expansion_gpio_read(comm_blade_rf_->blade_rf(),
				&check, __FILE__, __LINE__), __FILE__, __LINE__);
			if(switch_setting == (check & switch_mask))
				break;
		}
		if(switch_setting != (check & switch_mask))
			throw blade_rf_error("Unable to set xb gpio pins.");
	}

	set_parameter_cache(measurement_info(0, frequency, blade_bandwidth, blade_sampling_rate, gain));
}

void blade_rf_controller::set_gain(const gain_type &gain) {
	auto cache = parameter_cache();
	if(cache.gain().lna_gain_ != gain.lna_gain_) {
		check_blade_status(nr_set_lna_gain(comm_blade_rf_->blade_rf(), convert(gain.lna_gain_), __FILE__, __LINE__), __FILE__, __LINE__);
	}
	if(cache.gain().rxvga1_ != gain.rxvga1_) {
		check_blade_status(nr_set_rxvga1(comm_blade_rf_->blade_rf(), gain.rxvga1_, __FILE__, __LINE__), __FILE__, __LINE__);
	}
	if(cache.gain().rxvga2_ != gain.rxvga2_) {
		check_blade_status(nr_set_rxvga2(comm_blade_rf_->blade_rf(), gain.rxvga2_, __FILE__, __LINE__), __FILE__, __LINE__);
	}
	set_parameter_cache_gain(gain);
}

void blade_rf_controller::set_parameter_cache_gain(const gain_type &gain) {
	std::lock_guard<std::mutex> lock(parameter_cache_mutex_);
	parameter_cache_.gain(gain);
}

measurement_info blade_rf_controller::stream_rf_data_use_auto_gain(frequency_type frequency, time_type time_ns, time_type time_ns_to_overlap, bandwidth_type bandwidth, frequency_type sampling_rate) {
	if(!streaming_thread_ || !streaming_thread_->joinable() || frequency != parameter_cache_.frequency() || bandwidth != parameter_cache_.bandwidth() || sampling_rate != parameter_cache_.sampling_rate()) {
		// Auto gain changes streaming to intermittent which causes us to stop full streaming, if already going.
		// so we just pull the latest value and adjust within the streaming thread.  This is possible because
		// the blade config functions use a mutex.
		auto gain = gain_manager_.calculate_new_gain(frequency, bandwidth);
		configure_rf_parameters(frequency, bandwidth, gain, sampling_rate);
		should_update_streaming_parameters_ = true;

		{
			// Wait for nuand buffers to fill with new data.  Clear old data from measurement buffer.
			std::this_thread::sleep_for(std::chrono::nanoseconds(2 * time_ns + time_ns_to_overlap));
			std::lock_guard<std::mutex> lock(meas_buffer_mutex_);
			meas_buffer_.clear();
		}

		if(is_streaming_ != FULL_STREAMING || time_ns != streaming_time_ns_ || time_ns_to_overlap != streaming_time_ns_to_overlap_) {
			if(time_ns_to_overlap > time_ns) {
				throw misc_error("The total time for streaming must be larger than the overlap time.");
			}

			stop_streaming();

			streaming_time_ns_ = time_ns;
			streaming_time_ns_to_overlap_ = time_ns_to_overlap;

			enable_full_streaming_rx();

			streaming_thread_.reset(new std::thread([this](time_type time_ns, time_type time_ns_to_overlap) {
				try {
					auto cache = parameter_cache();
					auto sampling_rate = cache.sampling_rate();
					auto bandwidth = cache.bandwidth();
					auto frequency = cache.frequency();
					auto gain = cache.gain();

					auto meas_samples = convert_to_samples_and_mod_1024(time_ns, sampling_rate);
					auto num_overlap_samples = rf_phreaker::convert_to_samples(time_ns_to_overlap, cache.sampling_rate());
					auto num_transfer_samples = num_overlap_samples;
					auto copy_loc = meas_samples - num_overlap_samples;
					rf_stream_buffer_.reset(num_overlap_samples);
					bool first_time = true;
					int gain_count = 0;

					if(num_overlap_samples <= 0)
						throw rf_phreaker_error("There needs to be at least sample of overlap when streaming.");

					while(is_streaming_ == FULL_STREAMING) {
						if(should_update_streaming_parameters_) {
							should_update_streaming_parameters_ = false;
							num_overlap_samples = rf_phreaker::convert_to_samples(time_ns_to_overlap, cache.sampling_rate());
							first_time = true;
							gain_count = 0;
							cache = parameter_cache();
							sampling_rate = cache.sampling_rate();
							bandwidth = cache.bandwidth();
							frequency = cache.frequency();
							gain = cache.gain();
						}
						const auto return_bytes = (num_transfer_samples)* 2 * sizeof(int16_t);

						aligned_buffer_.align_array(return_bytes);
						auto aligned_buffer = aligned_buffer_.get_aligned_array();

						bladerf_metadata metadata;
						metadata.flags = BLADERF_META_FLAG_RX_NOW;

						int status = nr_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
							num_transfer_samples, &metadata, 2500);

						//if((metadata.flags & BLADERF_META_STATUS_OVERRUN) == BLADERF_META_STATUS_OVERRUN)
						//	LOG(LINFO) << "Buffer overrun occurred while streaming.  Restarting stream...";
						//else 
						if(status == 0) {
							// For now we use the computer time.  In the future perhaps we can use timestamp coming from the hardware.
							auto start_time = get_collection_start_time();

							measurement_info data(meas_samples, frequency, bandwidth, sampling_rate, gain,
								std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time),
								scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustments(gain.lna_gain_, frequency, bandwidth),
								scanner_blade_rf_->eeprom_.cal_.get_rf_board_adjustments(frequency, bandwidth, bandwidth),
								collection_count_++, scanner_blade_rf_->eeprom_.cal_.nuand_serial_);
							
							data.get_iq().zero_out();

							if(first_time) {
								ipp_helper::check_status(ippsConvert_16s32f(((Ipp16s*)&(*aligned_buffer_.get_aligned_array())),
									(Ipp32f*)rf_stream_buffer_.get(), rf_stream_buffer_.length() * 2));
								first_time = false;
								num_transfer_samples = meas_samples - num_overlap_samples;
								continue;
							}

							ipp_helper::check_status(ippsConvert_16s32f(((Ipp16s*)&(*aligned_buffer_.get_aligned_array())),
								(Ipp32f*)data.get_iq().get(num_overlap_samples), num_transfer_samples * 2));

							// Zero in on gain. Do this only on the new samples and only in the beginning of streaming. 
							// It's possible this may occur while blade_rf_controller is adjusting 
							// the gain, however this should be ok given that the blade function uses a mutex.
							if(gain_count++ < 3) {
								update_gain(data);
								gain = gain_manager_.calculate_new_gain(frequency, bandwidth);
								set_gain(gain);
							}
							data.get_iq().copy(rf_stream_buffer_.get(), num_overlap_samples);

							rf_stream_buffer_.copy(data.get_iq().get(copy_loc), num_overlap_samples);

							ipp_helper::subtract_dc(data.get_iq().get(), data.get_iq().length());

							std::lock_guard<std::mutex> lock(meas_buffer_mutex_);
							meas_buffer_.push_back(data);
						}
						else {
							LOG(LDEBUG) << "Collecting " << num_transfer_samples << " samples failed. Status = " << status << ".";
							// If status does not equal zero and we're still supposed to be streaming, throw an exception.
							if(is_streaming_ == FULL_STREAMING)
								throw blade_rf_error(std::string("Error collecting data samples. ") + nr_strerror(status));
						}
					}
				}
				catch(const std::exception &err) {
					LOG(LERROR) << "Encountered error while attempting to stream. " << err.what();
				}
				std::lock_guard<std::mutex> lock(meas_buffer_mutex_);
				meas_buffer_.clear();
			}, time_ns, time_ns_to_overlap));
			std::this_thread::sleep_for(std::chrono::nanoseconds(2 * time_ns + time_ns_to_overlap));
		}
	}
	return pop_measurement_buffer();
}

measurement_info blade_rf_controller::pop_measurement_buffer() {
	auto start = std::chrono::high_resolution_clock::now();
	while(streaming_thread_ && streaming_thread_->joinable()) {
		if(!meas_buffer_.empty()) {
			std::lock_guard<std::mutex> lock(meas_buffer_mutex_);
			if(!meas_buffer_.empty()) {
				auto meas = meas_buffer_.back();
				meas_buffer_.pop_back();
				return meas;
			}
		}
#ifdef _DEBUG
		if(0) {
#else
		// Timeout should be longer than nuand usb timeout.
		if(std::chrono::high_resolution_clock::now() - start > std::chrono::seconds(3)) {
#endif			
			is_streaming_ = NOT_STREAMING;
			LOG(LERROR) << "A timeout occurred while waiting on blade_rf_controller streaming thread.";
			break;
		}
	}
	throw rf_phreaker_error("Error streaming data.");
}

void blade_rf_controller::stop_streaming() {
	is_streaming_ = NOT_STREAMING;
	if(streaming_thread_ && streaming_thread_->joinable()) {
		streaming_thread_->join();
	}
	if(streaming_thread_)
		streaming_thread_.reset();
	streaming_time_ns_ = -1;
	streaming_time_ns_to_overlap_ = -1;
}

int blade_rf_controller::check_blade_status(int return_status, const std::string &file, int line)
{
	if(return_status < 0)
		throw blade_rf_error("[" + split_file_name(file) + (line == -1 ? "" : " L: " + std::to_string(line)) + "] BladeRF error: " + nr_strerror(return_status)
			+ ".", return_status);
	return return_status;
}

void blade_rf_controller::check_blade_comm()
{
	if(comm_blade_rf_.get() == nullptr)
		throw rf_phreaker::comm_error("It does not appear there is a valid connection to the device.  Try opening the device.");
}

void blade_rf_controller::write_flash(const std::vector<uint8_t> &bytes, const eeprom_addressing &addressing) {
	check_blade_comm();
	stop_streaming_and_disable_blade_rx();
	
	// Erase flash.
	check_blade_status(nr_erase_flash(comm_blade_rf_->blade_rf(),
		addressing.erase_block_address(), addressing.erase_block_length(), __FILE__, __LINE__), __FILE__, __LINE__);

	// Perform writes.
	check_blade_status(nr_write_flash(comm_blade_rf_->blade_rf(), &bytes[0],
		addressing.page_address(), addressing.page_length(), __FILE__, __LINE__), __FILE__, __LINE__);
}

std::vector<uint8_t> blade_rf_controller::read_flash(const eeprom_addressing &addressing) {
	check_blade_comm();
	stop_streaming_and_disable_blade_rx();

	std::vector<uint8_t> bytes(addressing.byte_length());

	check_blade_status(nr_read_flash(comm_blade_rf_->blade_rf(), &bytes[0],
		addressing.page_address(), addressing.page_length(), __FILE__, __LINE__), __FILE__, __LINE__);

	return bytes;
}

void blade_rf_controller::initialize_eeprom()
{
	eeprom ee;
	write_eeprom(ee);
}

void blade_rf_controller::write_eeprom_meta_data(const eeprom_meta_data &meta_ee)
{
	if(!meta_ee.is_valid())
		throw hardware_info_error("Cannot write EEPROM meta data.  It is not valid.");

	std::vector<uint8_t> md_bytes(meta_ee.addressing().byte_length(), 0);
	
	auto bytes = meta_ee.serialize_to_bytes();

	write_flash(bytes, meta_ee.addressing());
}

eeprom_meta_data blade_rf_controller::read_eeprom_meta_data() {
	auto bytes = read_flash(eeprom_meta_data::addressing());

	eeprom_meta_data md_eeprom;

	if(!md_eeprom.init(bytes))
		throw hardware_info_error("EEPROM meta data is not valid.");

	return md_eeprom;
}

void blade_rf_controller::write_eeprom(const eeprom &ee)
{
	eeprom_meta_data meta_ee;
	meta_ee.calculate_eeprom_addresses(ee);

	// Ensure we can serialize before writing anything to the EEPROM.
	auto bytes = ee.serialize_to_bytes();

	write_eeprom_meta_data(meta_ee);

	write_flash(bytes, meta_ee.trimmed_eeprom_addressing());
}

eeprom blade_rf_controller::read_eeprom(bool quick_read)
{
	eeprom ee;

	if(quick_read) {
		ee.freq_correction_ = read_frequency_correction_container();
		ee.license_ = read_license();
		ee.cal_ = read_calibration();
	}
	else {
		// Initialization gives us the default meta.
		eeprom_meta_data meta_ee;
		try {
			meta_ee = read_eeprom_meta_data();
		}
		catch(const rf_phreaker_error &err) {
			LOG(LERROR) << err.what() << "  Attempting to use default EEPROM meta data.";
		}
		auto bytes = read_flash(meta_ee.trimmed_eeprom_addressing());
		ee.init(bytes, meta_ee);
	}

	return ee;
}

void blade_rf_controller::write_calibration(calibration &cal)
{
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto cali_bytes = cal.serialize_to_bytes();

	// First check to see if we exceed the erase page boundary.  If ok, make sure eeprom meta data is correct.
	if(meta_ee.is_calibration_boundary_exceeded(cali_bytes.size())) {
		LOG(LINFO) << "Calibration size exceeds broundary.  Attempting to reformat EEPROM before writing calibration.";
		auto eeprom = read_eeprom();
		eeprom.cal_ = cal;
		write_eeprom(eeprom);
	}
	else{
		if(meta_ee.calibration_addressing().byte_length() != cali_bytes.size()) {
			LOG(LINFO) << "Updating EEPROM meta data with new calibration byte size.";
			meta_ee.update_calibration_length(cali_bytes.size());
			write_eeprom_meta_data(meta_ee);
		}
		write_flash(cali_bytes, meta_ee.calibration_addressing());
	}
}

calibration blade_rf_controller::read_calibration()
{
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto bytes = read_flash(meta_ee.calibration_addressing());

	calibration cal;
	if(!cal.init(bytes))
		throw hardware_info_error("Calibration failed initialization.", CALIBRATION_ERROR);
	return cal;
}

void blade_rf_controller::write_license(const license &license)
{
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto license_bytes = license.serialize_to_bytes(RF_PHREAKER_FLASH_PAGE_SIZE);

	// First check to see if we exceed the erase page boundary.  If ok, make sure eeprom meta data is correct.
	if(meta_ee.is_license_boundary_exceeded(license_bytes.size())) {
		LOG(LINFO) << "License size exceeds it's boundary.  Attempting to reformat EEPROM before writing license.";
		auto eeprom = read_eeprom();
		eeprom.license_ = license;
		write_eeprom(eeprom);
	}
	else {
		if(meta_ee.license_addressing().byte_length() != license_bytes.size()) {
			LOG(LINFO) << "Updating EEPROM meta data with new license byte size.";
			meta_ee.update_license_length(license_bytes.size());
			write_eeprom_meta_data(meta_ee);
		}
		write_flash(license_bytes, meta_ee.license_addressing());
	}
}

license blade_rf_controller::read_license() {
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto bytes = read_flash(meta_ee.license_addressing());

	license lic;
	if(!lic.init(bytes))
		delegate_sink::instance().log_error(std::string("License failed initialization."), hardware_info_error_type, LICENSE_ERROR);
	return lic;
}

void blade_rf_controller::write_frequency_correction(const freq_correction_container &freq_correction) {
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto corr_bytes = freq_correction.serialize_to_bytes();

	// First check to see if we exceed the erase page boundary.  If ok, make sure eeprom meta data is correct.
	if(meta_ee.is_license_boundary_exceeded(corr_bytes.size())) {
		LOG(LINFO) << "Frequency correction size exceeds it's boundary.  Attempting to reformat EEPROM before writing frequency correction.";
		auto eeprom = read_eeprom();
		eeprom.freq_correction_ = freq_correction;
		write_eeprom(eeprom);
	}
	else {
		if(meta_ee.freq_correction_addressing().byte_length() != corr_bytes.size()) {
			LOG(LINFO) << "Updating EEPROM meta data with new frequency correction byte size.";
			meta_ee.update_frequency_correction_length(corr_bytes.size());
			write_eeprom_meta_data(meta_ee);
		}
		write_flash(corr_bytes, meta_ee.freq_correction_addressing());
	}
}

freq_correction_container blade_rf_controller::read_frequency_correction_container() {
	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	auto bytes = read_flash(meta_ee.freq_correction_addressing());

	freq_correction_container con;
	if(!con.init(bytes)) {
		delegate_sink::instance().log_error(std::string("Frequency correction data failed initialization."),
			hardware_info_error_type, FREQUENCY_CORRECTION_VALUE_INVALID);
	}
	else if(con.nuand_freq_correction_value_ == 0) {
		delegate_sink::instance().log_error(std::string("Frequency correction data is invalid."),
			hardware_info_error_type, FREQUENCY_CORRECTION_VALUE_INVALID);
	}
	return con;
}

void blade_rf_controller::set_log_level(int level) {
	switch(level) {
	case 0:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_VERBOSE);
		break;
	case 1:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_DEBUG);
		break;
	case 2:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
		break;
	case 3:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_WARNING);
		break;
	case 4:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_ERROR);
		break;
	case 5:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_CRITICAL);
		break;
	case 6:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_SILENT);
		break;
	default:
		nr_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
	}
}

void blade_rf_controller::set_blade_sync_rx_settings(const blade_rx_settings &settings) {
	blade_settings_ = settings;
}

void blade_rf_controller::set_blade_sync_rx_stream_settings(const blade_rx_settings &settings) {
	blade_settings_stream_ = settings;
}

void blade_rf_controller::start_gps_1pps_integration(int seconds) {
	LOG(LDEBUG) << "Starting GPS calibration.  Integrating over " << seconds << " seconds.";
	if(gps_comm_) {
		gps_comm_->initiate_pps_clock_counter(seconds);
	}
	current_1pps_integration_.reset(seconds);
}

bool blade_rf_controller::attempt_gps_1pps_calibration() {
	bool success = false;
	if(gps_comm_) {
		current_1pps_integration_.set_clock_ticks(gps_comm_->read_pps_clock_counter(), gps_comm_->get_latest_gps().coordinated_universal_time_);
		LOG(LDEBUG) << "Retrieving GPS clock ticks:  " << current_1pps_integration_.clock_ticks() << ".";
		LOG_IF(LDEBUG, (current_1pps_integration_.clock_ticks() != 0)) << "Error based on clock ticks: " << current_1pps_integration_.error_in_hz() << " Hz.";
		if(current_1pps_integration_.is_valid()) {
			if(current_1pps_integration_.within_tolerance()) {
				last_1pps_integration_ = current_1pps_integration_;
				auto new_trim = calculate_vctcxo_trim_value(current_1pps_integration_.error_in_hz());
				update_vctcxo_trim(new_trim);
				success = true;
				LOG(LDEBUG) << "GPS calibration successful!";
			}
			else
				LOG(LDEBUG) << "GPS calibration failed.  Clock ticks were not within tolerance.";
		}
		else
			LOG(LDEBUG) << "GPS calibration failed.  Clock ticks not recorded.";
	}
	return success;
}

gps_1pps_integration blade_rf_controller::get_last_valid_gps_1pps_integration() {
	return last_1pps_integration_;
}

void blade_rf_controller::enable_continuity_check() {
	uint32_t gpio = 0;
	nr_config_gpio_read(comm_blade_rf_->blade_rf(), &gpio);
	gpio |= 0x200;
	nr_config_gpio_write(comm_blade_rf_->blade_rf(), gpio);
}

void blade_rf_controller::output_continuity_packet(int num_transfer_samples) {
	auto aligned_buffer = aligned_buffer_.get_aligned_array();
	std::ofstream debug_rx("debug_rx_samples.txt");
	debug_rx << *(uint32_t*)aligned_buffer << "\t" << *((uint32_t*)aligned_buffer + num_transfer_samples - 1) << std::endl;
}

}}