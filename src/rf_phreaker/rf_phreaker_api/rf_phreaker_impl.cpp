#include "rf_phreaker/rf_phreaker_api/rf_phreaker_impl.h"
#include "rf_phreaker/rf_phreaker_api/log_handler.h"
#include "rf_phreaker/rf_phreaker_api/data_wrappers.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_conversion.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/processing/collection_info_container.h"
#include "rf_phreaker/processing/frequency_range_creation.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/qt_specific/file_path_validation.h"
#include "tbb/task_scheduler_init.h"

namespace rf_phreaker { namespace api { 


rf_phreaker_impl& rf_phreaker_impl::instance() {
	static rf_phreaker_impl impl;
	return impl;
}

rf_phreaker_impl::rf_phreaker_impl() 
	: is_initialized_(false) {
}

rf_phreaker_impl::~rf_phreaker_impl() {
	try {
		// Do not stop graphs as this will cause an access volation in std::mutex.
		logger_.reset();
		gps_graph_.reset();
		processing_graph_.reset();
		frequency_correction_graph_.reset();
		data_output_.reset();
		handler_.reset();
		scanners_.clear();
	}
	catch(...) {}
}

rp_status rf_phreaker_impl::initialize(rp_callbacks *callbacks) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		read_settings();

		// If logging fails continue anyway.
		try {
			if(!file_path_validation::is_path_valid(config_.output_directory_))
				file_path_validation::make_path(config_.output_directory_);
			logger_.reset(new logger("rf_phreaker_api", config_.output_directory_));
		}
		catch(...) {}
		is_initialized_ = false;

		if(logger_) {
			logger_->change_logging_level(config_.log_level_);
			logger_->handler_.worker->addSink(std2::make_unique<log_handler>(callbacks), &log_handler::receive_log_message);
		}

		LOG(LINFO) << "Initializing rf phreaker api version " << build_version() << ".";

		// Release all components before changing delegate.
		handler_.release();
		scanners_.clear();
		data_output_.release();
		if(processing_graph_) {
			LOG(LDEBUG) << "Found processing graph on heap.  Sending cancel request and releasing it.";
			processing_graph_->cancel_and_wait();
			processing_graph_.release();
		}
		if(gps_graph_) {
			LOG(LDEBUG) << "Found gps graph on heap.  Sending cancel request and releasing it.";
			gps_graph_->cancel_and_wait();
			gps_graph_.release();
		}

		if(frequency_correction_graph_) {
			LOG(LDEBUG) << "Found frequency correction graph on heap.  Sending cancel request and releasing it.";
			frequency_correction_graph_->cancel_and_wait();
			frequency_correction_graph_.release();
		}

		data_output_.reset(new processing::data_output_async());
		handler_.reset(new rf_phreaker_handler(data_output_.get(), callbacks));
		processing_graph_.reset(new processing::processing_graph());
		gps_graph_.reset(new processing::gps_graph());
		frequency_correction_graph_.reset(new processing::frequency_correction_graph());

		data_output_->set_file_output(config_.file_output_);
		data_output_->set_standard_output(config_.standard_output_);
		data_output_->set_signal_output(config_.signal_slots_);

		processing::initialize_collection_info_defaults(config_);

		//tbb::task_scheduler_init init;
		//init.initialize(15);

		LOG(LINFO) << "Initialization complete.";
		is_initialized_ = true;
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

void rf_phreaker_impl::read_settings() {
	settings_io io("rf_phreaker_api", "cappeen");

	io.read(config_);
}

rp_status rf_phreaker_impl::clean_up() {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		LOG(LINFO) << "Cleaning up...";
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		// Do more!
		if(processing_graph_) {
			LOG(LVERBOSE) << "Waiting for processing graph...";
			processing_graph_->cancel_and_wait();
		}
		if(gps_graph_) {
			LOG(LVERBOSE) << "Waiting for gps graph...";
			gps_graph_->cancel_and_wait();
		}
		if(frequency_correction_graph_) {
			LOG(LVERBOSE) << "Waiting for frequency correction graph...";
			frequency_correction_graph_->cancel_and_wait();
		}
		gps_graph_.reset();
		processing_graph_.reset();
		frequency_correction_graph_.reset();
		data_output_.reset();
		handler_.reset();
		scanners_.clear();
		LOG(LINFO) << "Cleaned up successfully.";
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}

	try {
		logger_.reset();
	}
	catch(...) {}

	return s;
}

rp_status rf_phreaker_impl::list_devices(rp_serial *serials, int *num_serials) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		LOG(LINFO) << "Listing devices...";

		if(!is_initialized_)
			throw rf_phreaker_api_error("Not initialized.", RP_STATUS_NOT_INITIALIZED);
		else if(serials == nullptr)
			throw rf_phreaker_api_error("Null serials.", RP_STATUS_INVALID_PARAMETER);
		else if(num_serials == nullptr)
			throw rf_phreaker_api_error("Null num_serials.", RP_STATUS_INVALID_PARAMETER);
		else if(*num_serials <= 0)
			throw rf_phreaker_api_error("num_serials <= 0.", RP_STATUS_INVALID_PARAMETER);

		for(int i = 0; i < *num_serials; ++i)
			memset(serials[i].serial_, 0, RP_SERIAL_LENGTH);

		scanner::blade_rf_controller tmp_blade(rf_phreaker::scanner::USB_BLADE_RF);
		tmp_blade.set_log_level(config_.blade_settings_.log_level_);

		auto scanner_list = tmp_blade.list_available_scanners();
		// Sometimes the libbladeRF reports there is a connected device but does not give serial.
		// Requesting the list again seems to fix it.
		if(scanner_list.size() && (*scanner_list.begin())->id() == "")
			scanner_list = tmp_blade.list_available_scanners();

		if((size_t)*num_serials < scanner_list.size())
			throw rf_phreaker_api_error("Error while listing devices.  More devices than input buffer.", RP_STATUS_INVALID_PARAMETER);

		*num_serials = scanner_list.size();

		int i = 0;
		for(auto &device : scanner_list) 
			copy_serial(device->id(), serials[i++]);

		LOG(LINFO) << "Listed units successfully.";
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::connect_device(rp_serial serial, rp_device **device_ptr) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);
	
		LOG(LINFO) << "Opening device " << serial.serial_ << "...";

		if(!is_initialized_)
			throw rf_phreaker_api_error("Not initialized.", RP_STATUS_NOT_INITIALIZED);
		else if(serial.serial_ == nullptr)
			throw rf_phreaker_api_error("NULL serial.", RP_STATUS_INVALID_PARAMETER);
		else if(device_ptr == nullptr)
			throw rf_phreaker_api_error("NULL rp_device.", RP_STATUS_INVALID_PARAMETER);

		std::string serial_str(serial.serial_);
		for(auto &i : scanners_) {
			if(i->async_.get_scanner().get() != nullptr &&
				i->async_.get_scanner().get()->get_hardware().serial_ == serial_str) {
				LOG(LINFO) << "Device " << serial_str << " is already open.  Disconnecting device before reconnecting...";
				disconnect_device(i.get());
				break;
			}
		}

		scanners_.push_back(std::make_shared<rp_device>(rf_phreaker::scanner::USB_BLADE_RF));
		rp_device *device = scanners_.rbegin()->get();

		device->async_.set_log_level(config_.blade_settings_.log_level_);

		device->async_.open_scanner(serial.serial_).get();

		device->async_.do_initial_scanner_config(config_.blade_settings_).get();

		auto hw = device->async_.get_scanner().get()->get_hardware();
		
		handler_->output_device_info(hw);

		gps_graph_->start(&device->async_, data_output_.get(), config_);
		
		*device_ptr = device;

		LOG(LINFO) << "Opened device " << serial.serial_ << " successfully.";
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	} 
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}
	
rp_status rf_phreaker_impl::disconnect_device(rp_device *device) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		auto serial = device->async_.get_scanner().get()->get_hardware().serial_;

		LOG(LINFO) << "Disconnecting device " << serial << "...";

		if(frequency_correction_graph_)
			frequency_correction_graph_->cancel_and_wait();
		if(gps_graph_)
			gps_graph_->cancel_and_wait();
		if(processing_graph_)
			processing_graph_->cancel_and_wait();

		device->async_.close_scanner().get();

		// Remove this ptr and any scanner nulls that may be in there.
		scanners_.erase(std::find_if(scanners_.begin(), scanners_.end(), [&](const std::shared_ptr<rp_device> &p) {
			return p.get() == device || p.get()->async_.get_scanner().get() == nullptr;
		}), scanners_.end());

		LOG(LINFO) << "Closed device " << serial << " successfully.";
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

void rf_phreaker_impl::general_checks(rp_device *device) {
	if(!is_initialized_)
		throw rf_phreaker_api_error("Not initialized.", RP_STATUS_NOT_INITIALIZED);
	else if(!check_rp_device(device))
		throw rf_phreaker_api_error("Invalid rp_device.", RP_STATUS_INVALID_PARAMETER);
}

bool rf_phreaker_impl::is_device_open(rp_device *device) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		auto scanner = device->async_.get_scanner().get();
		if(!scanner)
			s = RP_STATUS_INVALID_PARAMETER;
		
		// If we get here then the scanner is valid and considered open.
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s == RP_STATUS_OK;
}

rp_status rf_phreaker_impl::get_device_info(rp_device *device, rp_device_info *device_info) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		if(!is_initialized_)
			throw rf_phreaker_api_error("Not initialized.", RP_STATUS_NOT_INITIALIZED);
		else if(!check_rp_device(device))
			throw rf_phreaker_api_error("Invalid rp_device.", RP_STATUS_INVALID_PARAMETER);

		*device_info = hardware_wrap(device->async_.get_scanner().get()->get_hardware()).buf_;
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::add_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band) {
	using namespace ::rf_phreaker::processing;
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		LOG(LINFO) << "Adding frequency (" << freq << ").";

		general_checks(device);

		auto hw = device->async_.get_scanner().get()->get_hardware();

		check_calibration(hw, freq);

		// Check for license.

		auto specifier = to_layer_3_specifier(data);
		auto it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
			return c.tech_ == specifier;
		});

		if(it == containers_.end()) {
			// If simultaneous collection is enabled we do not want to stop collection after one iteration of freqs.
			containers_.push_back(collection_info_container(specifier, !config_.simultaneous_collection_));
			it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
				return c.tech_ == specifier;
			});
		}

		it->adjust(add_collection_info(create_tech_collection_info(specifier, (frequency_type)freq, to_operating_band(band))));

		// Add to processing graph?
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

void rf_phreaker_impl::check_calibration(hardware hw, frequency_type freq) {
	// Check for calibration.
	if(rf_phreaker::is_within_freq_paths(hw.frequency_paths_, freq))
		throw rf_phreaker_api_error("Frequency (" + std::to_string(freq / 1e6) + " mhz) is not within calibration limits.");
}

rp_status rf_phreaker_impl::remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band) {
	using namespace ::rf_phreaker::processing;
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		LOG(LINFO) << "Removing frequency (" << freq << ")";

		general_checks(device);

		auto specifier = to_layer_3_specifier(data);
		auto it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
			return c.tech_ == specifier;
		});

		if(it == containers_.end()) {
			it->adjust(remove_collection_info(create_tech_collection_info(specifier, (frequency_type)freq, to_operating_band(band))));
		}
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

//rp_status rf_phreaker_impl::add_collection_channel(rp_technology data, rp_channel_type channel) {
//	using namespace ::rf_phreaker::processing;
//	rp_status s = RP_STATUS_OK;
//	try {
//		std::lock_guard<std::recursive_mutex> lock(mutex_);
//
//		if(!is_initialized_)
//			throw rf_phreaker_api_error("Not initialized.", RP_STATUS_NOT_INITIALIZED);
//		else if(data == RAW_IQ)
//			throw rf_phreaker_api_error("Invalid rp_technology - RAW_IQ does not have associated channels.", RP_STATUS_INVALID_PARAMETER);
//
//		auto specifier = to_layer_3_specifier(data);
//		
//		
//	}
//	catch(const rf_phreaker_error &err) {
//		s = to_rp_status(err);
//	}
//	catch(const std::exception &) {
//		s = RP_STATUS_GENERIC_ERROR;
//	}
//	catch(...) {
//		s = RP_STATUS_UNKNOWN_ERROR;
//	}
//	return s;
//}

rp_status rf_phreaker_impl::add_sweep_operating_band(rp_device *device, rp_operating_band rp_band) {
	using namespace ::rf_phreaker::processing;
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		auto band = to_operating_band(rp_band);

		LOG(LINFO) << "Adding operating band (" << to_string(band) << ").";

		general_checks(device);

		auto hw = device->async_.get_scanner().get()->get_hardware();

		// Check for calibration.
		auto range = operating_bands_.get_band_freq_range(band);
		if(rf_phreaker::is_within_freq_paths(hw.frequency_paths_, range.low_freq_hz_, range.high_freq_hz_))
			throw rf_phreaker_api_error("rp_operating_band is not within calibration limits.  Start freq: " +
			std::to_string(range.low_freq_hz_ / 1e6) + ".  Stop freq: " + std::to_string(range.high_freq_hz_ / 1e6) + ".");

		// Check license.

		collection_info_containers::iterator it;

		if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND) {
			auto it = add_sweep(UMTS_SWEEP, UMTS_LAYER_3_DECODE);
			frequency_range_creation::adjust_umts_sweep_collection_info(range, *it);
		}
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND) {
			auto it = add_sweep(LTE_SWEEP, LTE_LAYER_3_DECODE);
			frequency_range_creation::adjust_lte_sweep_collection_info(range, *it);
		}
		else if(band >= FIRST_GSM_OPERATING_BAND && band <= LAST_GSM_OPERATING_BAND) {
			throw rf_phreaker_api_error("GSM not supported.");
			auto it = add_sweep(GSM_SWEEP, GSM_LAYER_3_DECODE);
			//frequency_range_creation::adjust_gsm_sweep_collection_info(range, *it);
		}
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

processing::collection_info_containers::iterator rf_phreaker_impl::add_sweep(specifier sweep, specifier decode) {
	using namespace ::rf_phreaker::processing;
	auto it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
		return c.tech_ == sweep;
	});
	if(it == containers_.end()) {
		containers_.push_back(collection_info_container(sweep, !config_.simultaneous_collection_));
		containers_.push_back(collection_info_container(decode, false));
		it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
			return c.tech_ == sweep;
		});
	}
	return it;
}

rp_status rf_phreaker_impl::remove_sweep_operating_band(rp_device *device, rp_operating_band rp_band) {
	using namespace ::rf_phreaker::processing;
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		auto band = to_operating_band(rp_band);

		LOG(LINFO) << "Removing operating band (" << to_string(band) << ")";

		general_checks(device);

		if(band >= FIRST_UMTS_OPERATING_BAND && band <= LAST_UMTS_OPERATING_BAND) {
			remove_sweep(band, UMTS_SWEEP);
		}
		else if(band >= FIRST_LTE_OPERATING_BAND && band <= LAST_LTE_OPERATING_BAND) {
			remove_sweep(band, LTE_SWEEP);
		}
		else if(band >= FIRST_GSM_OPERATING_BAND && band <= LAST_GSM_OPERATING_BAND) {
			remove_sweep(band, GSM_SWEEP);
		}
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

void rf_phreaker_impl::remove_sweep(operating_band band, specifier sweep) {
	using namespace ::rf_phreaker::processing;
	auto it = std::find_if(containers_.begin(), containers_.end(), [&](const collection_info_container &c) {
		return c.tech_ == sweep;
	});
	if(it != containers_.end()) {
		auto range = operating_bands_.get_band_freq_range(band);
		collection_info_container tmp;
		switch(sweep) {
		case UMTS_SWEEP:
			frequency_range_creation::adjust_umts_sweep_collection_info(range, tmp);
			break;
		case LTE_SWEEP:
			frequency_range_creation::adjust_lte_sweep_collection_info(range, tmp);
			break;
		case GSM_SWEEP:
//			frequency_range_creation::adjust_gsm_sweep_collection_info(range, tmp);
			break;
		default:
			;
		}
		for(auto &info : tmp.collection_info_group_)
			it->adjust(remove_collection_info(info));
	}
}

rp_status rf_phreaker_impl::start_collection(rp_device *device) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		LOG(LINFO) << "Starting collection.";

		general_checks(device);
	
		if(frequency_correction_graph_)
			frequency_correction_graph_->cancel_and_wait();
		if(processing_graph_)
			processing_graph_->cancel_and_wait();

		processing_graph_->start(&device->async_, data_output_.get(), containers_, config_);
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::stop_collection(rp_device *device) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);
	
		LOG(LINFO) << "Stopping collection.";

		if(processing_graph_)
			processing_graph_->cancel_and_wait();
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::get_gps_data(rp_device *device, rp_gps gps) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		LOG(LDEBUG) << "Retrieving GPS data.";

		auto g = device->async_.get_gps_data().get();

		gps = gps_wrap(g).buf_;
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, 
	rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, rp_raw_data *raw_data) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		if(raw_data == nullptr)
			throw rf_phreaker_api_error("Null rp_raw_data.", RP_STATUS_INVALID_PARAMETER);
		else if(time_ns < 0)
			throw rf_phreaker_api_error("Invalid time.", RP_STATUS_INVALID_PARAMETER);

		auto hw = device->async_.get_scanner();

		auto samples_required = rf_phreaker::convert_to_samples(time_ns, sampling_rate);
		if(samples_required > raw_data->num_samples_)
			throw rf_phreaker_api_error("Insufficient number of samples supplied.  At least " + std::to_string(samples_required)
			+ " samples are required.", RP_STATUS_INVALID_PARAMETER);

		auto meas = device->async_.get_rf_data(frequency, time_ns, bandwidth, sampling_rate).get();


		check_calibration(hw.get()->get_hardware(), frequency);

		// check license


		raw_data->base_.carrier_bandwidth_ = meas.bandwidth();
		raw_data->base_.carrier_frequency_ = meas.frequency();
		raw_data->base_.carrier_signal_level_ = 0;
		raw_data->base_.collection_round_ = meas.collection_round();
		copy_serial(meas.serial(), raw_data->base_.serial_);
		raw_data->base_.status_flags_ = 0;
		raw_data->base_.time_ = 0;
		raw_data->power_adjustment_ = meas.blade_adjustment() - config_.use_rf_board_adjustment_ ? meas.rf_board_adjustment() : 0;
		raw_data->sample_format_ = LITTLE_ENDIAN_FLOAT_REAL_IMAGINARY;
		if(meas.get_iq().length() < raw_data->num_samples_)
			raw_data->num_samples_ = meas.get_iq().length();
		memcpy(raw_data->samples_, meas.get_iq().get(), (size_t)raw_data->num_samples_ * sizeof(scanner::measurement_info::sample_type));
	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, 
	rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db, rp_raw_data *raw_data) {
	rp_status s = RP_STATUS_OK;
	try {
		throw rf_phreaker_api_error("get_iq_data with gain is not supported.");

		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		auto hw = device->async_.get_scanner();

		auto samples_required = rf_phreaker::convert_to_samples(time_ns, sampling_rate);
		if(samples_required > raw_data->num_samples_)
			throw rf_phreaker_api_error("Insufficient number of samples supplied.  At least " + std::to_string(samples_required)
			+ " samples are required.", RP_STATUS_INVALID_PARAMETER);

		//auto meas = device->async_.get_rf_data(frequency, time_ns, bandwidth, gain, sampling_rate).get();


		check_calibration(hw.get()->get_hardware(), frequency);

		// check license

	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

rp_status rf_phreaker_impl::update_license(rp_device *device, const char *filename) {
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		general_checks(device);

		if(filename == nullptr)
			throw rf_phreaker_api_error("filename is null", RP_STATUS_INVALID_PARAMETER);

		throw rf_phreaker_api_error("update_license is not supported.");

	}
	catch(const rf_phreaker_error &err) {
		s = to_rp_status(err);
	}
	catch(const std::exception &) {
		s = RP_STATUS_GENERIC_ERROR;
	}
	catch(...) {
		s = RP_STATUS_UNKNOWN_ERROR;
	}
	return s;
}

const char* rf_phreaker_impl::status_message(rp_status status) {
	char *s;
	switch(status) {
	case RP_STATUS_OK:
		s = "success";
	case RP_STATUS_NOT_INITIALIZED:
		s = "rf_phreaker is not initialized";
	case RP_STATUS_UNKNOWN_ERROR:
		s = "unknown error";
	default:
		s = "unknown status";
	}
	return s;
}

const char* rf_phreaker_impl::build_version() {
	return "0.0.0.1";
}



}}