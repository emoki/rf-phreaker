#include "rf_phreaker/scanner/blade_rf_controller.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/delegate_sink.h"
#include "rf_phreaker/scanner/comm_blade_rf.h"
#include "rf_phreaker/scanner/bandwidth_conversion.h"
#include "rf_phreaker/scanner/lms_utilities.h"
#include "rf_phreaker/scanner/scanner_utility.h"
#include "rf_phreaker/common/common_utility.h"
#include "rf_phreaker/scanner/scanner_blade_rf_impl.h"
#include "libbladeRF.h"
#include "boost/math/special_functions/round.hpp"
#include "boost/date_time.hpp"

namespace rf_phreaker { namespace scanner {

blade_rf_controller::blade_rf_controller(comm_type)
	: collection_count_(0)
{
	bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
}

blade_rf_controller::blade_rf_controller(blade_rf_controller &&c)
: comm_blade_rf_(std::move(c.comm_blade_rf_))
, scanner_blade_rf_(std::move(c.scanner_blade_rf_))
, collection_count_(std::move(c.collection_count_))
{}

blade_rf_controller::~blade_rf_controller()
{
	if(comm_blade_rf_.get()) {
		bladerf_close(comm_blade_rf_->blade_rf());
	}
}

int blade_rf_controller::num_available_scanners()
{
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = bladerf_get_device_list(&dev_info);

	// Sometimes the API reports 0 devices connected even tho we have a scanner connected. 
	// In which case we repeat the call.
	if(num_devices == BLADERF_ERR_NODEV) {
		for(int i = 0; i < 4; ++i) {
			num_devices = bladerf_get_device_list(&dev_info);
			if(num_devices > 0)
				break;
		}
	}

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV && num_devices < 0) {
		bladerf_free_device_list(dev_info);
		check_blade_status(num_devices, __FILE__, __LINE__);
	}

	bladerf_free_device_list(dev_info);

	return num_devices;
}

std::vector<comm_info_ptr> blade_rf_controller::list_available_scanners()
{
	std::vector<comm_info_ptr> devices;
	bladerf_devinfo *dev_info = nullptr;

	int num_devices = bladerf_get_device_list(&dev_info);

	// Sometimes the API reports 0 devices connected even tho we have a scanner connected. 
	// In which case we repeat the call.
	if(num_devices == BLADERF_ERR_NODEV) {
		for(int i = 0; i < 4; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			num_devices = bladerf_get_device_list(&dev_info);
			if(num_devices > 0)
				break;
		}
	}

	// We do not consider no blade devices connected to be an error here.
	if(num_devices != BLADERF_ERR_NODEV && num_devices < 0) {
		if(dev_info)
			bladerf_free_device_list(dev_info);
		check_blade_status(num_devices, __FILE__, __LINE__);
	}

	for(int i = 0; i < num_devices; i++) {
		devices.push_back(comm_info_ptr(new comm_blade_rf(dev_info[i])));
	}

	bladerf_free_device_list(dev_info);

	return devices;
}

void blade_rf_controller::open_scanner(const scanner_serial_type &id)
{
	parameter_cache_ = measurement_info();

	close_scanner();

	std::string open_str = "*:serial=" + id;

	bladerf *blade_rf;
	bladerf_devinfo dev_info;
	int retry = 0;
	while(1) {
		try {
			check_blade_status(bladerf_open(&blade_rf, open_str.c_str()), __FILE__, __LINE__);

			check_blade_status(bladerf_get_devinfo(blade_rf, &dev_info), __FILE__, __LINE__);
	
			break;
		}
		catch(rf_phreaker_error &err) {
			if(++retry > 8)
				throw err;
			LOG(LDEBUG) << err.what() << "  Attempting to reopen...";
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

	comm_blade_rf_.reset(new comm_blade_rf(dev_info, blade_rf));

	refresh_scanner_info();

	LOG(LDEBUG) << "Opened scanner " << scanner_blade_rf_->serial() << ".";
	LOG(LDEBUG) << "USB backend is " << usb_backend_to_string(scanner_blade_rf_->back_end()) << ".";
	LOG(LDEBUG) << "Device speed is " << to_string(scanner_blade_rf_->usb_speed()) << ".";
	LOG(LDEBUG) << "RF calibration performed on " << boost::posix_time::to_simple_string(boost::posix_time::from_time_t(scanner_blade_rf_->get_rf_calibration_date())) << ".";
	LOG(LDEBUG) << "VCTCXO trim value is " << scanner_blade_rf_->vctcxo_trim() << ".";
	LOG(LDEBUG) << "Frequency correction performed on " << boost::posix_time::to_simple_string(boost::posix_time::from_time_t(scanner_blade_rf_->get_frequency_correction_date())) << ".";
	LOG(LDEBUG) << "Frequency correction value is " << scanner_blade_rf_->get_frequency_correction_value() << ".";
}

void blade_rf_controller::refresh_scanner_info()
{
	check_blade_comm();

	scanner_blade_rf_impl blade;

	auto comm_blade = comm_blade_rf_->blade_rf();

	check_blade_status(bladerf_get_devinfo(comm_blade, &blade.dev_info_), __FILE__, __LINE__);

	blade.usb_speed_ = static_cast<bladerf_dev_speed>(check_blade_status(bladerf_device_speed(comm_blade_rf_->blade_rf()), __FILE__, __LINE__));

	bladerf_version(&blade.blade_rf_version_);

	check_blade_status(bladerf_fw_version(comm_blade, &blade.firmware_version_), __FILE__, __LINE__);

	check_blade_status(bladerf_fpga_version(comm_blade, &blade.fpga_version_), __FILE__, __LINE__);

	blade.rx_timeout_ = 0;

	check_blade_status(bladerf_get_vctcxo_trim(comm_blade, &blade.vctcxo_trim_value_), __FILE__, __LINE__);

	try {
		auto meta_eeprom = read_eeprom_meta_data();
		if(meta_eeprom.is_valid()) {
			blade.eeprom_ = read_eeprom();
		}
		else
			throw rf_phreaker_error("EEPROM meta data is invalid.");
	}
	catch(rf_phreaker_error &err) {
		LOG(LERROR) << "Error reading EEPROM.  " << err.what();
		delegate_sink::instance().log_error(std::string("Error reading EEPROM.  ") + err.what(), err.error_code_);

	}
	catch(std::exception &err) {
		LOG(LERROR) << "Error reading EEPROM.  " << err.what();
		delegate_sink::instance().log_error(std::string("Error reading EEPROM.  ") + err.what(), EEPROM_ERROR);

	}

	if(!scanner_blade_rf_) {
		scanner_blade_rf_ = std::make_shared<scanner_blade_rf_impl>(blade);
		scanner_ = std::make_shared<scanner_blade_rf>(scanner_blade_rf_.get());
	}
	else {
		*scanner_blade_rf_ = blade;
		*scanner_ = scanner_blade_rf_.get();
	}

	if(scanner_blade_rf_->eeprom_.cal_.nuand_freq_correction_value_ && scanner_blade_rf_->eeprom_.cal_.nuand_freq_correction_value_ != scanner_blade_rf_->vctcxo_trim_value_) {
		update_vctcxo_trim(scanner_blade_rf_->eeprom_.cal_.nuand_freq_correction_value_);
	}
}

void blade_rf_controller::close_scanner()
{
	if(comm_blade_rf_.get()) {
		bladerf_close(comm_blade_rf_->blade_rf());
		comm_blade_rf_.reset();
		scanner_blade_rf_.reset();
		scanner_.reset();
		gps_comm_.reset();
	}
}

void blade_rf_controller::do_initial_scanner_config(const scanner_settings &settings)
{
	check_blade_comm();

	std::string id = comm_blade_rf_->id();

	blade_settings_ = reinterpret_cast<const blade_settings&>(settings);

	// When errors opening and configuring occur they seem to be fixed
	// by restarting the entire process hence if an error occurs anywhere 
	// within the open/configure process we restart.
	int retry = 0;
	while(1) {
		try {
			check_blade_status(bladerf_load_fpga(comm_blade_rf_->blade_rf(),
				"fpga_load.rbf"), __FILE__, __LINE__);

			int status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_LPF_TUNING));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: LPF Tuning Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: LPF Tuning Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = check_blade_status(bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RX_LPF));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: DC RX LPT Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RX LPT Module.");

			status = 0;
			for(int i = 0; i < 2; ++i) {
				status = (bladerf_calibrate_dc(comm_blade_rf_->blade_rf(),
					BLADERF_DC_CAL_RXVGA2));
				if(status == 0) break;
				LOG(LDEBUG) << "Calibration attempt failed: DC RXVGA2 Module. Retrying...";
			}
			if(status)
				throw blade_rf_error("Calibration failed: DC RXVGA2 Module.");

			check_blade_status(bladerf_set_lpf_mode(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
				BLADERF_LPF_NORMAL), __FILE__, __LINE__);

			break;
		}
		catch(rf_phreaker_error &err) {
			if(++retry > 4)
				throw err;

			LOG(LDEBUG) << err.what() << "  Attempting to recover...";

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
		false), __FILE__, __LINE__);

	// TODO - Change this so that we only alter switch settings.
	check_blade_status(bladerf_expansion_gpio_dir_write(comm_blade_rf_->blade_rf(), 0xFFFFFFFF), __FILE__, __LINE__);

	enable_blade_rx();

	gps_comm_.reset(new gps_comm::gps_comm());
	gps_comm_->init(comm_blade_rf_->blade_rf(), false);
}

void blade_rf_controller::enable_blade_rx()
{
	if(blade_settings_.rx_sync_buffer_size_ % 1024 != 0) {
		blade_settings_.rx_sync_buffer_size_ = add_mod(blade_settings_.rx_sync_buffer_size_, 1024);
		LOG(LWARNING) << "The nuand rx sync buffer size is not a multiple of 1024.  Adjusting value to " << blade_settings_.rx_sync_buffer_size_ << ".";
	}
#ifdef _DEBUG
	check_blade_status(bladerf_sync_config(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		blade_settings_.rx_sync_num_buffers_, blade_settings_.rx_sync_buffer_size_, blade_settings_.rx_sync_num_transfers_, 
		blade_settings_.rx_sync_timeout_), __FILE__, __LINE__);
#else
	check_blade_status(bladerf_sync_config(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX, BLADERF_FORMAT_SC16_Q11,
		blade_settings_.rx_sync_num_buffers_, blade_settings_.rx_sync_buffer_size_, blade_settings_.rx_sync_num_transfers_,
		blade_settings_.rx_sync_timeout_), __FILE__, __LINE__);
#endif

	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		true), __FILE__, __LINE__);
}

void blade_rf_controller::disable_blade_rx()
{
	check_blade_status(bladerf_enable_module(comm_blade_rf_->blade_rf(),
		BLADERF_MODULE_RX,
		false), __FILE__, __LINE__);
}

void blade_rf_controller::calculate_vctcxo_trim_and_update_calibration(double error_hz)
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

	auto adjust = boost::math::round(error_hz / dac_trim_hz_per_lsb_coefficient() * .9);

	return scanner_blade_rf_->vctcxo_trim() - (int16_t)adjust;
}

void blade_rf_controller::write_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

	disable_blade_rx();

	auto image = bladerf_alloc_cal_image(BLADERF_FPGA_40KLE, trim);
	if(image == nullptr)
		throw blade_rf_error("Unable to create calibration image.");

	LOG(LDEBUG) << "Writing vctcxo trim value of " << trim << " to scanner " << comm_blade_rf_->id() << ".";

	auto page = BLADERF_FLASH_TO_PAGES(image->address);
	auto count = BLADERF_FLASH_TO_PAGES(image->length);

	check_blade_status(bladerf_erase_flash(comm_blade_rf_->blade_rf(), BLADERF_FLASH_EB_CAL, BLADERF_FLASH_EB_LEN_CAL), __FILE__, __LINE__);
	check_blade_status(bladerf_write_flash(comm_blade_rf_->blade_rf(), image->data, page, count), __FILE__, __LINE__);

	bladerf_free_image(image);

	enable_blade_rx();
}

void blade_rf_controller::update_frequency_correction_value_and_date_in_calibration(uint16_t value, time_t date)
{
	auto eeprom = read_eeprom();
	eeprom.cal_.nuand_freq_correction_value_ = value;
	eeprom.cal_.nuand_freq_correction_date_ = date;
	write_eeprom(eeprom);
}

void blade_rf_controller::calculate_and_update_vctcxo_trim(double error_hz)
{
	auto trim = calculate_vctcxo_trim_value(error_hz);
	update_vctcxo_trim(trim);
}

void blade_rf_controller::update_vctcxo_trim(uint16_t trim)
{
	check_blade_comm();

	disable_blade_rx();

	LOG(LDEBUG) << "Updating VCTCXO trim value to " << trim << ".";

	check_blade_status(bladerf_dac_write(comm_blade_rf_->blade_rf(), trim), __FILE__, __LINE__);
	
	if(scanner_blade_rf_)
		scanner_blade_rf_->vctcxo_trim_value_ = trim;

	enable_blade_rx();
}

void blade_rf_controller::read_vctcxo_trim(uint16_t &trim)
{
	check_blade_comm();

	if(scanner_blade_rf_)
		trim = scanner_blade_rf_->vctcxo_trim_value_;
	else
		check_blade_status(bladerf_get_vctcxo_trim(comm_blade_rf_->blade_rf(), &trim), __FILE__, __LINE__);
}

void blade_rf_controller::write_gpio(uint32_t value) {
	check_blade_comm();

	check_blade_status(bladerf_expansion_gpio_write(comm_blade_rf_->blade_rf(), value), __FILE__, __LINE__);
}

void blade_rf_controller::read_gpio(uint32_t &value) {
	check_blade_comm();

	check_blade_status(bladerf_expansion_gpio_read(comm_blade_rf_->blade_rf(), &value), __FILE__, __LINE__);
}

void blade_rf_controller::write_config_gpio(uint32_t value) {
	check_blade_comm();

	check_blade_status(bladerf_config_gpio_write(comm_blade_rf_->blade_rf(), value), __FILE__, __LINE__);
}

void blade_rf_controller::read_config_gpio(uint32_t &value) {
	check_blade_comm();

	check_blade_status(bladerf_config_gpio_read(comm_blade_rf_->blade_rf(), &value), __FILE__, __LINE__);
}

void blade_rf_controller::set_lms_reg(uint8_t address, uint8_t value)
{
	check_blade_comm();

	check_blade_status(bladerf_lms_write(comm_blade_rf_->blade_rf(), address, value), __FILE__, __LINE__);
}

void blade_rf_controller::read_lms_reg(uint8_t address, uint8_t &value)
{
	check_blade_comm();

	check_blade_status(bladerf_lms_read(comm_blade_rf_->blade_rf(), address, &value), __FILE__, __LINE__);
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
	if(gain_manager_.in_history(freq, bandwidth))
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
	uint32_t switch_setting, uint32_t switch_mask)
{
	LOG(LCOLLECTION) << "Taking snapshot... " << "frequency: " << frequency / 1e6 << "mhz | time: "
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
			LOG(LDEBUG) << "Setting frequency (" << frequency / 1e6 << "mhz) failed. Retrying...";
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
		check_blade_status(bladerf_set_lna_gain(comm_blade_rf_->blade_rf(), convert(gain.lna_gain_)), __FILE__, __LINE__);
	}
	if(parameter_cache_.gain().rxvga1_ != gain.rxvga1_) {
		check_blade_status(bladerf_set_rxvga1(comm_blade_rf_->blade_rf(), gain.rxvga1_), __FILE__, __LINE__);
	}
	if(parameter_cache_.gain().rxvga2_ != gain.rxvga2_) {
		check_blade_status(bladerf_set_rxvga2(comm_blade_rf_->blade_rf(), gain.rxvga2_), __FILE__, __LINE__);
	}
	
	unsigned int blade_sampling_rate = 0;
	unsigned int blade_bandwidth = 0;

	if(parameter_cache_.sampling_rate() != sampling_rate) {
		check_blade_status(bladerf_set_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			static_cast<uint32_t>(sampling_rate), &blade_sampling_rate), __FILE__, __LINE__);
	}
	else
		blade_sampling_rate = static_cast<uint32_t>(parameter_cache_.sampling_rate());

	if(parameter_cache_.bandwidth() != bandwidth) {
		check_blade_status(bladerf_set_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
			bandwidth, &blade_bandwidth), __FILE__, __LINE__);
	}
	else
		blade_bandwidth = parameter_cache_.bandwidth();

	uint32_t gpio_in_hw = 0;
	check_blade_status(bladerf_expansion_gpio_read(comm_blade_rf_->blade_rf(),
		&gpio_in_hw), __FILE__, __LINE__);
	LOG(LCOLLECTION) << "Current xb gpio:" << gpio_in_hw << ".";

	if(switch_mask == 0) {
		auto auto_switch_setting = scanner_blade_rf_->eeprom_.cal_.get_rf_switch(frequency);
		switch_setting = auto_switch_setting.switch_setting_;
		switch_mask = auto_switch_setting.switch_mask_;
	}
	if((gpio_in_hw & switch_mask) != switch_setting) {
		gpio_in_hw &= ~switch_mask;
		uint32_t new_gpio = gpio_in_hw | switch_setting;
		check_blade_status(bladerf_expansion_gpio_write(comm_blade_rf_->blade_rf(),
			new_gpio), __FILE__, __LINE__);
		LOG(LCOLLECTION) << "Setting xb gpio to " << new_gpio << ".";
		uint32_t tmp = 0;
		check_blade_status(bladerf_expansion_gpio_read(comm_blade_rf_->blade_rf(),
			&tmp), __FILE__, __LINE__);
		if(switch_setting != (tmp & switch_mask))
			throw hardware_error("Unable to set xb gpio pins.");
	}
	// BladeRF only accepts data num_samples that are a multiple of 1024.
	// Because the blade rx sync parameters are configurable we want to make sure we 
	// clear out every buffer.
	int throw_away_samples = blade_settings_.rx_sync_buffer_size_ * blade_settings_.rx_sync_num_buffers_;

	int num_samples = rf_phreaker::convert_to_samples(time_ns, blade_sampling_rate);
	auto num_samples_to_transfer = add_mod(num_samples, 1024);

	const auto return_bytes = (num_samples_to_transfer + throw_away_samples) * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	bladerf_metadata metadata;

	int status = 0;
	for(int i = 0; i < 10; ++i) {
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples_to_transfer + throw_away_samples, &metadata, 2500);
		if(status == 0) 
			break;
		LOG(LDEBUG) << "Collecting " << num_samples_to_transfer + throw_away_samples << " samples failed. Status = " << status << ". Retrying...";
		disable_blade_rx();
		enable_blade_rx();
	}
	if(status)
		throw blade_rf_error(std::string("Error collecting data samples.  ") + bladerf_strerror(status));

	parameter_cache_ = measurement_info(0, frequency, blade_bandwidth, blade_sampling_rate , gain);

	measurement_info data(num_samples, frequency, blade_bandwidth, blade_sampling_rate, gain, 
		scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustment(frequency),
		scanner_blade_rf_->eeprom_.cal_.get_rf_board_adjustment(frequency),
		collection_count_++, scanner_blade_rf_->eeprom_.cal_.nuand_serial_);

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

	check_blade_comm();

	check_blade_status(bladerf_get_lna_gain(comm_blade_rf_->blade_rf(), &tmp_lna_gain), __FILE__, __LINE__);
	gain.lna_gain_ = convert(tmp_lna_gain);

	check_blade_status(bladerf_get_rxvga1(comm_blade_rf_->blade_rf(), &gain.rxvga1_), __FILE__, __LINE__);

	check_blade_status(bladerf_get_rxvga2(comm_blade_rf_->blade_rf(), &gain.rxvga2_), __FILE__, __LINE__);

	check_blade_status(bladerf_get_sample_rate(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		&blade_sampling_rate), __FILE__, __LINE__);

	check_blade_status(bladerf_get_bandwidth(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		&blade_bandwidth), __FILE__, __LINE__);

	check_blade_status(bladerf_get_frequency(comm_blade_rf_->blade_rf(), BLADERF_MODULE_RX,
		&frequency), __FILE__, __LINE__);

	// BladeRF only accepts data num_samples that are a multiple of 1024.
	num_samples = add_mod(num_samples, 1024);

	const auto return_bytes = num_samples * 2 * sizeof(int16_t);

	aligned_buffer_.align_array(return_bytes);
	auto aligned_buffer = aligned_buffer_.get_aligned_array();

	bladerf_metadata metadata;

	int status = 0;
	for(int i = 0; i < 10; ++i) {
#ifdef _DEBUG
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples, &metadata, 0);
#else
		status = bladerf_sync_rx(comm_blade_rf_->blade_rf(), aligned_buffer,
			num_samples, &metadata, 2500);
#endif
		if(status == 0) 
			break;
		LOG(LDEBUG) << "Collecting " << return_bytes << " samples failed. Retrying...";
		disable_blade_rx();
		enable_blade_rx();
	}
	if(status)
		throw blade_rf_error(std::string("Error collecting data samples.  ") + bladerf_strerror(status));

	measurement_info data(num_samples, frequency, blade_bandwidth, blade_sampling_rate, gain,
		scanner_blade_rf_->eeprom_.cal_.get_nuand_adjustment(frequency),
		scanner_blade_rf_->eeprom_.cal_.get_rf_board_adjustment(frequency),
		collection_count_++, scanner_blade_rf_->eeprom_.cal_.nuand_serial_);

	for(int i = 0; i < num_samples * 2; ++i)
		sign_extend_12_bits(reinterpret_cast<int16_t*>(aligned_buffer)[i]);

	ipp_helper::check_status(ippsConvert_16s32f((Ipp16s*)&(*aligned_buffer_.get_aligned_array()),
		(Ipp32f*)data.get_iq().get(), data.get_iq().length() * 2));

	ipp_helper::subtract_dc(data.get_iq().get(), data.get_iq().length());

	return data;
}

int blade_rf_controller::check_blade_status(int return_status, const std::string &file, int line)
{
	if(return_status < 0)
		throw blade_rf_error("[" + split_file_name(file) + " L: " + std::to_string(line) + "] BladeRF error: " + bladerf_strerror(return_status)
			+ ".", return_status);
	return return_status;
}

void blade_rf_controller::check_blade_comm()
{
	if(comm_blade_rf_.get() == nullptr)
		throw rf_phreaker::comm_error("It does not appear there is a valid connection to the device.  Try opening the device.");
}

void blade_rf_controller::initialize_eeprom()
{
	check_blade_comm();
	eeprom ee;
	write_eeprom(ee);
}

eeprom_meta_data blade_rf_controller::read_eeprom_meta_data()
{
	check_blade_comm();

	disable_blade_rx();

	std::vector<uint8_t> md_bytes(eeprom_meta_data::absolute_total_byte_length(), 0);

	check_blade_status(bladerf_read_flash(comm_blade_rf_->blade_rf(), &md_bytes[0],
		eeprom_meta_data::absolute_page_address(), eeprom_meta_data::absolute_total_page_length()));

	eeprom_meta_data md_eeprom;
	md_eeprom.init(md_bytes);
	
	return md_eeprom;
}

void blade_rf_controller::write_eeprom(const eeprom &ee)
{
	check_blade_comm();

	disable_blade_rx();

	auto new_eeprom_bytes = ee.serialize_to_bytes();

	eeprom_meta_data meta_ee;
	meta_ee.set_eeprom_byte_length_and_calculate_address(new_eeprom_bytes.size());
	auto meta_bytes = meta_ee.serialize_to_bytes();

	if(!meta_ee.is_valid())
		throw rf_phreaker_error("Cannot write to the EEPROM.  EEPROM meta data is not valid.", EEPROM_ERROR);

	// Erase flash.
	check_blade_status(bladerf_erase_flash(comm_blade_rf_->blade_rf(),
		eeprom::absolute_erase_block_address(), eeprom::absolute_erase_block_length()));

	// Perform writes.
	check_blade_status(bladerf_write_flash(comm_blade_rf_->blade_rf(), &meta_bytes[0],
		eeprom_meta_data::absolute_page_address(), eeprom_meta_data::absolute_total_page_length()));

	check_blade_status(bladerf_write_flash(comm_blade_rf_->blade_rf(), &new_eeprom_bytes[0],
		meta_ee.eeprom_page_address(), meta_ee.eeprom_page_length()));
}

eeprom blade_rf_controller::read_eeprom()
{
	check_blade_comm();

	disable_blade_rx();

	eeprom_meta_data meta_ee = read_eeprom_meta_data();

	if(!meta_ee.is_valid())
		throw rf_phreaker_error("Cannot read EEPROM.  EEPROM meta data is not valid.", EEPROM_ERROR);

	std::vector<uint8_t> bytes(eeprom::absolute_total_byte_length(), 0);

	check_blade_status(bladerf_read_flash(comm_blade_rf_->blade_rf(), &bytes[0],
		meta_ee.eeprom_page_address(), meta_ee.eeprom_page_length()));

	eeprom ee;
	ee.init(bytes);

	return ee;
}

void blade_rf_controller::write_calibration(calibration & cal)
{
	eeprom ee = read_eeprom();
	ee.cal_ = cal;
	write_eeprom(ee);
}

calibration blade_rf_controller::read_calibration()
{
	eeprom ee = read_eeprom();
	return ee.cal_;
}

void blade_rf_controller::write_license(const license &lic)
{
	eeprom ee = read_eeprom();
	ee.license_ = lic;
	write_eeprom(ee);
}

void blade_rf_controller::set_log_level(int level) {
	switch(level) {
	case 0:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_VERBOSE);
		break;
	case 1:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_DEBUG);
		break;
	case 2:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
		break;
	case 3:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_WARNING);
		break;
	case 4:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_ERROR);
		break;
	case 5:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_CRITICAL);
		break;
	case 6:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_SILENT);
		break;
	default:
		bladerf_log_set_verbosity(BLADERF_LOG_LEVEL_INFO);
	}
}

void blade_rf_controller::set_blade_sync_rx_settings(const blade_settings &settings) {
	blade_settings_ = settings;

	enable_blade_rx();
}

void blade_rf_controller::start_gps_1pps_integration(int seconds) {
	LOG(LDEBUG) << "Starting GPS calibration.  Integrating over " << seconds << " seconds.";
	if(gps_comm_) {
		gps_comm_->initiate_pps_clock_counter(seconds);
	}
	current_1pps_integration_ = {seconds, 0};
}

bool blade_rf_controller::attempt_gps_1pps_calibration() {
	bool success = false;
	if(gps_comm_) {
		current_1pps_integration_.set_clock_ticks(gps_comm_->read_pps_clock_counter(), gps_comm_->get_latest_gps().coordinated_universal_time_);
		LOG(LDEBUG) << "Retrieving GPS calibration values:  " << current_1pps_integration_.clock_ticks() << " clock ticks.  Error of "
			<< current_1pps_integration_.error_in_hz() << " Hz.";
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

}}