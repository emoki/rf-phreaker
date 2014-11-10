#include "rf_phreaker/rf_phreaker_api/rf_phreaker_impl.h"
#include "rf_phreaker/common/exception_types.h"
#include "rf_phreaker/common/log.h"
#include "rf_phreaker/qt_specific/settings_io.h"
#include "rf_phreaker/rf_phreaker_api/rf_phreaker_api_converter.h"
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
		//delegate_.release();
		scanner_.release();
		data_output_.release();
		processing_graph_.release();
		gps_graph_.release();
		frequency_correction_graph_.release();
		logger_.release();
	}
	catch(...) {}
}

rp_status rf_phreaker_impl::initialize(rp_callbacks *callbacks) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;
	
	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

		try {
			logger_.reset(new logger("rf_phreaker_api", ""));
		}
		catch(...) {}

		LOG(LINFO) << "Initializing rf phreaker api version " << build_version() << ".";

		is_initialized_ = false;

		LOG(LVERBOSE) << "Reading settings.";
		read_settings();

		//if(logger_)
		//	logger_->log_worker_->changeLoggingLevel(config_.log_level_);

		// Release all components before changing delegate.
		//delegate_.release();
		scanner_.release();
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


		//delegate_.reset(new cappeen_delegate(del));
		scanner_.reset(new scanner::blade_rf_controller_async(rf_phreaker::scanner::USB_BLADE_RF));
		data_output_.reset(new processing::data_output_async());
		processing_graph_.reset(new processing::processing_graph());
		gps_graph_.reset(new processing::gps_graph());
		frequency_correction_graph_.reset(new processing::frequency_correction_graph());

		//delegate_->initialize(data_output_.get(), processing_graph_.get(), gps_graph_.get());
		//log_worker_->connect_sink(boost::bind(&cappeen_delegate::output_error, delegate_.get(), _1, _2));

		data_output_->set_file_output(config_.file_output_);
		data_output_->set_standard_output(config_.standard_output_);
		data_output_->set_signal_output(config_.signal_slots_);

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
	//	settings_io io("rf_phreaker_api", "rf_phreaker");
	settings_io io("rf_phreaker_api.ini");

	io.read(config_);
}


rp_status rf_phreaker_impl::clean_up() {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::list_devices(rp_serial_type *serials, int *num_serials) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::connect_device(const rp_serial_type *serial, rp_device **device) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::is_device_open(rp_device *device) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::get_device_info(rp_device *device, rp_device_info *device_info) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::add_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::remove_collection_frequency(rp_device *device, rp_technology data, rp_frequency_type freq, rp_operating_band band) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::remove_collection_channel(rp_device *device, rp_technology data, rp_channel_type channel) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::add_sweep_operating_band(rp_device *device, rp_operating_band band) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::remove_sweep_operating_band(rp_device *device, rp_operating_band band) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::get_iq_data_using_auto_gain(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate, int32_t gain_db) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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

rp_status rf_phreaker_impl::get_iq_data(rp_device *device, rp_frequency_type frequency, rp_time_type time_ns, rp_bandwidth_type bandwidth, rp_frequency_type sampling_rate) {
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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
	if(!is_initialized_)
		return RP_STATUS_NOT_INITIALIZED;

	rp_status s = RP_STATUS_OK;
	try {
		std::lock_guard<std::recursive_mutex> lock(mutex_);

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